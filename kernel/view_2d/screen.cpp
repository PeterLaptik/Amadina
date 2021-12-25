#include "Screen.h"
#include "../command/command.h"

// Default borders positions
// I.e. default screen is [0, 0, 200, 200]
static const double DEFAULT_LEFT_BORDER = 0;
static const double DEFAULT_RIGHT_BORDER = 200;
static const double DEFAULT_TOP_BORDER = 200;
static const double DEFAULT_BOTTOM_BORDER = 0;

// Zoom multiplier
// Each step of mouse wheel rotation will change
// screen scale by ZOOM_COEFF times
static const double ZOOM_COEFF = 1.1;

// Minimum screen size
// Screen cannot be zoomed in for width / height less than MIN_MARGIN
static const double MIN_MARGIN = 0.1;

// Default value of snap radius in pixels
static const int SCREEN_SNAP_RADIUS = 5;

// Keyboard commands
static const char KEY_ENTER = 13;


Screen::Screen():
        m_screen_state(SCR_NOTHING),
        m_is_wheel_pressed(false),
        m_context(this),
        m_receiver(nullptr)
{
    m_borders.left = DEFAULT_LEFT_BORDER;
    m_borders.right = DEFAULT_RIGHT_BORDER;
    m_borders.top = DEFAULT_TOP_BORDER;
    m_borders.bottom = DEFAULT_BOTTOM_BORDER;
}


Screen::~Screen()
{ }


// The method should be called each time on derived panel resizing.
// Recalculates screen ratios
void Screen::ScreenResize(const int &width, const int &height)
{
    m_width = width;
    m_height = height;
    // Keep right proportions for a drafting
    double scr_ratio = static_cast<double>(height)/ static_cast<double>(width);
    if(scr_ratio<=1)
        m_borders.right = m_borders.left + (m_borders.top - m_borders.bottom)/scr_ratio;
    else
        m_borders.bottom = m_borders.top - scr_ratio*(m_borders.right - m_borders.left);

    CalculateBestSnapRadius();
    RefreshScreen();
}

// The method should be called each time on mouse wheel event over a derived panel.
// Recalculates screen scale
void Screen::ScreenMouseWheel(const int &direction, const int &coord_x, const int &coord_y)
{
    double zoom_x = ((m_borders.right - m_borders.left)*ZOOM_COEFF - (m_borders.right - m_borders.left))/2;
    double zoom_y = ((m_borders.top - m_borders.bottom)*ZOOM_COEFF - (m_borders.top - m_borders.bottom))/2;
    if(direction<0)
    {
        // TODO
        // Check for maximum values
        m_borders.right += zoom_x;
        m_borders.left -= zoom_x;
        m_borders.top += zoom_y;
        m_borders.bottom -= zoom_y;
    }
    else
    {
        // Ignore scaling if the margin is too small
        if((m_borders.right - m_borders.left<MIN_MARGIN)
           ||(m_borders.top - m_borders.bottom<MIN_MARGIN))
            return;

        m_borders.right -= zoom_x;
        m_borders.left += zoom_x;
        m_borders.top -= zoom_y;
        m_borders.bottom += zoom_y;
    }
    // Calibrate screen position to mouse pointer
    // I.e. scaling has to be performed closer to the current mouse pointer position
    double current_x = static_cast<double>(coord_x);
    double current_y = static_cast<double>(coord_y);
    TransformCoordinatesToGlobal(current_x, current_y);
    double delta_x = current_x - m_mouse_coord.x;
    double delta_y = current_y - m_mouse_coord.y;
    m_borders.right -= delta_x;
    m_borders.left -= delta_x;
    m_borders.top -= delta_y;
    m_borders.bottom -= delta_y;
    CalculateBestSnapRadius();
    RefreshScreen();
}

// TODO
void Screen::ScreenMouseLeftButtonClicked(const int &coord_x,
                                  const int &coord_y,
                                  const bool &is_ctrl_pressed)
{
    if(is_ctrl_pressed)
        return; // Do not pick points on screen dragging

    double x = static_cast<double>(coord_x);
    double y = static_cast<double>(coord_y);
    TransformCoordinatesToGlobal(x, y);
    m_mouse_coord.x = x;
    m_mouse_coord.y = y;

    switch(m_screen_state)
    {
    case SCR_PICKING:
        PointPicked(x, y);
        RefreshScreen();
        return;
    case SCR_SELECTING:
    case SCR_NOTHING:
        m_draw_manager.SelectInPoint(x, y, m_snap_radius/2);
        RefreshScreen();
        break;
    }
    return;
}

void Screen::ScreenMouseLeftButtonUp(const int &coord_x, const int &coord_y)
{
    m_mouse_coord.x = static_cast<double>(coord_x);
    m_mouse_coord.y = static_cast<double>(coord_y);
    TransformCoordinatesToGlobal(m_mouse_coord.x, m_mouse_coord.y);
}

void Screen::ScreenMouseWheelUp(const int &coord_x, const int &coord_y)
{
    m_is_wheel_pressed = false;
}

void Screen::ScreenMouseWheelDown(const int &coord_x, const int &coord_y)
{
    double x = static_cast<double>(coord_x);
    double y = static_cast<double>(coord_y);
    TransformCoordinatesToGlobal(x, y);
    m_mouse_coord.x = x;
    m_mouse_coord.y = y;
    m_is_wheel_pressed = true;
}

void Screen::ScreenMouseMove(const int &coord_x, const int &coord_y,
                              const bool &is_ctrl_pressed,
                              const bool &is_lb_pressed)
{
    double x = static_cast<double>(coord_x);
    double y = static_cast<double>(coord_y);
    TransformCoordinatesToGlobal(x, y);
    if((!m_is_wheel_pressed)&&(!((is_ctrl_pressed)&&(is_lb_pressed)))) // move by wheel pressed or mouse left button + ctrl
    {
        m_mouse_coord.x = x;
        m_mouse_coord.y = y;
        RefreshScreen();
        return;
    }

    // TODO
    // Check maximum borders
    double delta_x = m_mouse_coord.x - x;
    double delta_y = m_mouse_coord.y - y;
    m_borders.left += delta_x;
    m_borders.right += delta_x;
    m_borders.top += delta_y;
    m_borders.bottom += delta_y;
    RefreshScreen();
}

// Calculates snap radius value in a real coordinates
void Screen::CalculateBestSnapRadius()
{
    double dummy_y1 = 0;
    double dummy_y2 = 0;
    double dummy_x1 = 0;
    double dummy_x2 = SCREEN_SNAP_RADIUS;
    TransformCoordinatesToGlobal(dummy_x1, dummy_y1);
    TransformCoordinatesToGlobal(dummy_x2, dummy_y2);
    m_snap_radius = dummy_x2 - dummy_x1;
}

// Recalculates coordinates values from a local values on a panel into a global values
void Screen::TransformCoordinatesToGlobal(double &x, double &y)
{
    x = m_borders.left + x/static_cast<double>(m_width)*(m_borders.right - m_borders.left);
    y = m_borders.bottom + (static_cast<double>(m_height) - y)/static_cast<double>(m_height)*(m_borders.top - m_borders.bottom);
}

void Screen::ScreenKeyPressed(char key)
{
    // Selection accepted
    switch(key)
    {
        case KEY_ENTER:
            if(m_screen_state==SCR_SELECTING && m_receiver)
            {
                m_receiver->SetEntities(m_draw_manager.GetSelection());
                m_draw_manager.ClearSelection();
                m_context.Update();
            }
            break;
    }
}

void Screen::PointPicked(double x, double y)
{
    Point *snap_point = m_draw_manager.GetSnapPoint();
    if(m_receiver && m_screen_state==SCR_PICKING)
        m_receiver->SetPoint(snap_point ? *snap_point : Point(x,y));
}

void Screen::ClearSelection()
{
    m_draw_manager.ClearSelection();
    RefreshScreen();
}

const std::vector<Entity*>& Screen::GetSelection()
{
    return m_draw_manager.GetSelection();
}

void Screen::AppendEntity(Entity *entity)
{
    if(!entity)
        return;
    m_draw_manager.ClearSelection();
    m_draw_manager.AddEntity(entity);
    RefreshScreen();
}

void Screen::AppendEntities(const std::vector<Entity*> &entities)
{
    m_draw_manager.ClearSelection();
    for(std::vector<Entity*>::const_iterator it=entities.begin();
            it!=entities.end(); ++it)
        m_draw_manager.AddEntity(*it);
    RefreshScreen();
}

void Screen::DeleteEntity(Entity *entity)
{
    if(!entity)
        return;
    m_draw_manager.ClearSelection();
    m_draw_manager.DeleteEntity(entity);
    RefreshScreen();
}

void Screen::DeleteEntities(const std::vector<Entity*> &entities)
{
    // TODO: packaged remove
    m_draw_manager.ClearSelection();
    for(std::vector<Entity*>::const_iterator it=entities.begin();
            it!=entities.end(); ++it)
        m_draw_manager.DeleteEntity(*it);

    RefreshScreen();
}

void Screen::RedrawAll(IAdapterDC &dc)
{
    dc.CadClear();
    dc.SetBorders(m_borders.left, m_borders.right, m_borders.top, m_borders.bottom);
    dc.SetBackgroundColour(m_colour);

    if(m_receiver)
    {
        dc.CadSetColour(m_colour.IsDark() ? Colours::WHITE : Colours::BLACK);
        m_receiver->Redraw(dc, m_mouse_coord.x, m_mouse_coord.y);
    }

    m_context.Update();
    m_draw_manager.DrawAll(dc);

    if(m_screen_state==SCR_NOTHING)
    {
        m_draw_manager.ShowSnapEntities(dc, m_mouse_coord.x, m_mouse_coord.y, m_snap_radius/2);
    }

    if(m_screen_state!=SCR_NOTHING
       && m_screen_state!=SCR_SELECTING)
    {
        m_draw_manager.ShowSnapPoints(dc, m_mouse_coord.x, m_mouse_coord.y, m_snap_radius);
    }

//    if(m_shape_builder)
//        m_shape_builder->Redraw(dc, m_mouse_coord.x, m_mouse_coord.y);
}

//DrawManager* Screen::GetDrawManager()
//{
//    return &m_draw_manager;
//}

//void Screen::ScreenSetSizeInPixels(const int &width, const int &height)
//{
//    m_width = width;
//    m_height = height;
//}

void Screen::SetBorders(const double &left,
                        const double &right,
                        const double &top,
                        const double &bottom)
{
    m_borders.left = left;
    m_borders.right = right;
    m_borders.top = top;
    m_borders.bottom = bottom;
}

void Screen::GetBorders(double *left,
                        double *right,
                        double *top,
                        double *bottom) const
{
    *left = m_borders.left;
    *right = m_borders.right;
    *top = m_borders.top;
    *bottom = m_borders.bottom;
}

void Screen::SetState(InteractiveState state)
{
    m_screen_state = state;
}

InteractiveState Screen::GetState()
{
    return m_screen_state;
}
