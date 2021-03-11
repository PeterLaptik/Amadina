#include "adapter.h"
#include "../builders/abstractbuilder.h"

// Default borders positions
static const double DEFAULT_LEFT_BORDER = 0;
static const double DEFAULT_RIGHT_BORDER = 200;
static const double DEFAULT_TOP_BORDER = 200;
static const double DEFAULT_BOTTOM_BORDER = 0;

// Zoom multiplier
static const double ZOOM_COEFF = 1.1;

// Minimum and maximum screen sizes
static const double MIN_MARGIN = 0.1;


Adapter::Adapter(int width, int height):
        m_screen_width(width),
        m_screen_height(height),
        m_screen_state(SCR_NOTHING),
        m_is_wheel_pressed(false),
        m_shape_builder(nullptr)
{
    m_borders.left = DEFAULT_LEFT_BORDER;
    m_borders.right = DEFAULT_RIGHT_BORDER;
    m_borders.top = DEFAULT_TOP_BORDER;
    m_borders.bottom = DEFAULT_BOTTOM_BORDER;
}


Adapter::~Adapter()
{ }


// The method should be called each time on derived panel resizing.
// Recalculates screen ratios
void Adapter::ScreenResize(const int &width, const int &height)
{
    // Keep right proportions for a drafting
    double scr_ratio = static_cast<double>(height)/ static_cast<double>(width);
    if(scr_ratio<=1)
        m_borders.right = m_borders.left + (m_borders.top - m_borders.bottom)/scr_ratio;
    else
        m_borders.bottom = m_borders.top - scr_ratio*(m_borders.right - m_borders.left);

    CalculateBestSnapRadius();
}

// The method should be called each time on mouse wheel event over a derived panel.
// Recalculates screen scale
void Adapter::ScreenMouseWheel(const int &direction, const int &coord_x, const int &coord_y)
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
    double current_y = static_cast<double>(coord_x);
    TransformCoordinatesToGlobal(current_x, current_y);
    double delta_x = current_x - m_mouse_coord.x;
    double delta_y = current_y - m_mouse_coord.y;
    m_borders.right -= delta_x;
    m_borders.left -= delta_x;
    m_borders.top -= delta_y;
    m_borders.bottom -= delta_y;
    CalculateBestSnapRadius();
}

// TODO
bool Adapter::ScreenMouseLBClicked(const int &coord_x,
                                  const int &coord_y,
                                  const bool &is_ctrl_pressed)
{
    if(is_ctrl_pressed)
        return false; // Do not pick points on screen dragging

    double x = static_cast<double>(coord_x);
    double y = static_cast<double>(coord_y);
    TransformCoordinatesToGlobal(x, y);
    m_mouse_coord.x = x;
    m_mouse_coord.y = y;

    switch(m_screen_state)
    {
    case SCR_PICKING:
        PointPicked(x, y);
        return true;
        break;
    case SCR_NOTHING:
        //draw_manager.SelectInPoint(x, y, m_snap_radius/2);
        break;
    }
    return false;
}

void Adapter::ScreenMouseLeftButtonUp(const int &coord_x, const int &coord_y)
{
    m_mouse_coord.x = static_cast<double>(coord_x);
    m_mouse_coord.y = static_cast<double>(coord_x);
    TransformCoordinatesToGlobal(m_mouse_coord.x, m_mouse_coord.y);
}

void Adapter::ScreenMouseWheelUp(const int &coord_x, const int &coord_y)
{
    m_is_wheel_pressed = false;
}

void Adapter::ScreenMouseWheelDown(const int &coord_x, const int &coord_y)
{
    double x = static_cast<double>(coord_x);
    double y = static_cast<double>(coord_y);
    TransformCoordinatesToGlobal(x, y);
    m_mouse_coord.x = x;
    m_mouse_coord.y = y;
    m_is_wheel_pressed = true;
}

void Adapter::ScreenMouseMove(const int &coord_x, const int &coord_y,
                              const bool &is_ctrl_pressed,
                              const bool &is_lb_pressed)
{
    double x = static_cast<double>(x);
    double y = static_cast<double>(y);
    TransformCoordinatesToGlobal(x, y);
    if((!m_is_wheel_pressed)&&(!((is_ctrl_pressed)&&(is_lb_pressed)))) // move by wheel pressed or mouse left button + ctrl
    {
        m_mouse_coord.x = x;
        m_mouse_coord.y = y;
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
}

// Calculates snap radius value in a real coordinates
void Adapter::CalculateBestSnapRadius()
{
    double dummy_y1 = 0;
    double dummy_y2 = 0;
    double dummy_x1 = 0;
    double dummy_x2 = 5;
    TransformCoordinatesToGlobal(dummy_x1, dummy_y1);
    TransformCoordinatesToGlobal(dummy_x2, dummy_y2);
    m_snap_radius = dummy_x2 - dummy_x1;
}

// Recalculates coordinates values from a local values on a panel into a global values
void Adapter::TransformCoordinatesToGlobal(double &x, double &y)
{
    x = m_borders.left + x/static_cast<double>(m_width)*(m_borders.right - m_borders.left);
    y = m_borders.bottom + (static_cast<double>(m_height) - y)/static_cast<double>(m_height)*(m_borders.top - m_borders.bottom);
}

void Adapter::PointPicked(double x, double y)
{
    if(!m_shape_builder)
        return;

    Point pt(x,y);
    Point *snap_point = m_draw_manager.GetSnapPoint();
    if(snap_point)
        pt = *snap_point;

    bool result = m_shape_builder->AppendPoint(pt);
    bool multishape = m_shape_builder->IsMultiBuild();
    if((result)&&(!multishape))
    {
        Entity *entity = m_shape_builder->Create();
        m_draw_manager.AddEntity(entity);
        m_screen_state = SCR_NOTHING;
        delete m_shape_builder;
        m_shape_builder = nullptr;
    }
    if((result)&&(multishape))
    {
        Entity *entity = m_shape_builder->Create();
        m_draw_manager.AddEntity(entity);
        if(!entity)
        {
            m_screen_state = SCR_NOTHING;
            delete m_shape_builder;
            m_shape_builder = nullptr;
        }
    }
}

void Adapter::CreateEntity(AbstractBuilder *builder)
{
    if(!builder)
        return;

    // Reset selection if exists
    m_draw_manager.ClearSelection();

    // TODO other states compatibility
    m_screen_state = SCR_PICKING;

    // Reassign builder
    if(m_shape_builder!=nullptr)
        delete m_shape_builder;
    m_shape_builder = builder;
}

void Adapter::CancelCommand()
{
    m_screen_state = SCR_NOTHING;
    if(m_shape_builder)
    {
        delete m_shape_builder;
        m_shape_builder = nullptr;
    }
    m_draw_manager.ClearSelection();
}

void Adapter::RedrawAll(IAdapterDC &dc)
{
    dc.CadClear();
    dc.SetBorders(m_borders.left, m_borders.right, m_borders.top, m_borders.bottom);
    dc.SetBackgroundColour(Colour(70, 70, 70));

    if(m_screen_state==SCR_NOTHING)
    {
        m_draw_manager.ShowSnapEntities(dc, m_mouse_coord.x, m_mouse_coord.y, m_snap_radius/2);
    }

    if(m_screen_state!=SCR_NOTHING)
    {
        m_draw_manager.ShowSnapPoints(dc, m_mouse_coord.x, m_mouse_coord.y, m_snap_radius);
    }

    m_draw_manager.DrawAll(dc);

    //if(m_shape_builder)
        //m_shape_builder->Redraw(dc, m_mouse_coord.x, m_mouse_coord.y);
}

DrawManager& Adapter::GetDrawManager()
{
    return m_draw_manager;
}

void Adapter::SetBorders(const double &left,
                        const double &right,
                        const double &top,
                        const double &bottom)
{
    m_borders.left = left;
    m_borders.right = right;
    m_borders.top = top;
    m_borders.bottom = bottom;
}

void Adapter::GetBorders(double *left,
                        double *right,
                        double *top,
                        double *bottom) const
{
    *left = m_borders.left;
    *right = m_borders.right;
    *top = m_borders.top;
    *bottom = m_borders.bottom;
}

