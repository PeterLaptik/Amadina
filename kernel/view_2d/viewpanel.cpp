#include "viewpanel.h"
#include "../graphics/dcadapter_wx.h"
#include "../entities/line.h"
#include "../entities/circle.h"
#include "../entities/square.h"
#include <wx/dcclient.h>

#define TEST_MODE

// Default borders positions
static const double DEFAULT_LEFT_BORDER = 0;
static const double DEFAULT_RIGHT_BORDER = 200;
static const double DEFAULT_TOP_BORDER = 200;
static const double DEFAULT_BOTTOM_BORDER = 0;

// Zoom multiplier
static const double ZOOM_COEFF = 1.1;

// Minimum and maximum screen sizes
static const double MIN_MARGIN = 0.1;

static const int DEFAULT_COLOUR_VALUE = 0;


wxBEGIN_EVENT_TABLE(ViewPanel, wxPanel)
    EVT_PAINT(ViewPanel::OnPaint)
    EVT_SIZE(ViewPanel::OnResize)
    EVT_LEFT_DOWN(ViewPanel::OnMouseLeftButtonDown)
    EVT_LEFT_UP(ViewPanel::OnMouseLeftButtonUp)
    EVT_MOTION(ViewPanel::OnMouseMove)
    EVT_MOUSEWHEEL(ViewPanel::OnMouseWheel)
    EVT_MIDDLE_DOWN(ViewPanel::OnMouseWheelDown)
    EVT_MIDDLE_UP(ViewPanel::OnMouseWheelUp)
wxEND_EVENT_TABLE()


ViewPanel::ViewPanel(wxWindow *parent,
                     wxWindowID winid,
                    const wxPoint &pos,
                    const wxSize &size,
                    long style,
                    const wxString &name):
    wxPanel(parent, winid, pos, size, style, name)
{
    wheel_pressed = false;
    canvas_state = STATE_NOTHING;
    shape_builder = nullptr;
    borders.left = DEFAULT_LEFT_BORDER;
    borders.right = DEFAULT_RIGHT_BORDER;
    borders.top = DEFAULT_TOP_BORDER;
    borders.bottom = DEFAULT_BOTTOM_BORDER;
    this->GetSize(&width_px, &height_px);
    this->SetBackgroundStyle(wxBG_STYLE_PAINT);
    this->SetBackgroundColour(wxColour(DEFAULT_COLOUR_VALUE, DEFAULT_COLOUR_VALUE, DEFAULT_COLOUR_VALUE));
    #ifdef TEST_MODE
        //AddTestShapes();
    #endif // TEST_MODE
}

ViewPanel::~ViewPanel()
{
    if(shape_builder!=nullptr)
        delete shape_builder;
}

void ViewPanel::OnMouseMove(wxMouseEvent &event)
{
    bool is_ctrl_pressed = wxGetKeyState(WXK_RAW_CONTROL);
    bool is_lb_pressed = wxGetMouseState().LeftIsDown();
    double x = static_cast<double>(event.GetX());
    double y = static_cast<double>(event.GetY());
    TransformCoordinatesToGlobal(x, y);
    if((!wheel_pressed)&&(!((is_ctrl_pressed)&&(is_lb_pressed)))) // move by wheel pressed or mouse left button + ctrl
    {
        coordinates.x = x;
        coordinates.y = y;
        this->Refresh();
        return;
    }

    // TODO
    // Check maximum borders
    double delta_x = coordinates.x - x;
    double delta_y = coordinates.y - y;
    borders.left += delta_x;
    borders.right += delta_x;
    borders.top += delta_y;
    borders.bottom += delta_y;
    this->Refresh();
}

void ViewPanel::OnMouseWheelDown(wxMouseEvent &event)
{
    double x = static_cast<double>(event.GetX());
    double y = static_cast<double>(event.GetY());
    TransformCoordinatesToGlobal(x, y);
    coordinates.x = x;
    coordinates.y = y;
    wheel_pressed = true;
}

void ViewPanel::PointPicked(double x, double y)
{
    if(!shape_builder)
        return;

    Point pt(x,y);
    Point *snap_point = draw_manager.GetSnapPoint();
    if(snap_point)
        pt = *snap_point;

    bool result = shape_builder->AppendPoint(pt);
    bool multishape = shape_builder->IsMultiBuild();
    if((result)&&(!multishape))
    {
        Entity *entity = shape_builder->Create();
        draw_manager.AddEntity(entity);
        canvas_state = STATE_NOTHING;
        delete shape_builder;
        shape_builder = nullptr;
    }
    if((result)&&(multishape))
    {
        Entity *entity = shape_builder->Create();
        draw_manager.AddEntity(entity);
        if(!entity)
        {
            canvas_state = STATE_NOTHING;
            delete shape_builder;
            shape_builder = nullptr;
        }
    }
}


void ViewPanel::OnMouseWheelUp(wxMouseEvent &event)
{
    wheel_pressed = false;
}

void ViewPanel::OnMouseLeftButtonDown(wxMouseEvent &event)
{
    if(wxGetKeyState(WXK_RAW_CONTROL))
        return; // Do not pick points on screen dragging

    double x = static_cast<double>(event.GetX());
    double y = static_cast<double>(event.GetY());
    TransformCoordinatesToGlobal(x, y);
    coordinates.x = x;
    coordinates.y = y;

    switch(canvas_state)
    {
    case STATE_PICKING_POINTS:
        PointPicked(x, y);
        this->Refresh();
        break;
    }
}

void ViewPanel::OnMouseLeftButtonUp(wxMouseEvent &event)
{
    coordinates.x = static_cast<double>(event.GetX());
    coordinates.y = static_cast<double>(event.GetY());
    TransformCoordinatesToGlobal(coordinates.x, coordinates.y);
}

void ViewPanel::OnMouseWheel(wxMouseEvent &event)
{
    int delta = event.GetWheelRotation();
    double zoom_x = ((borders.right - borders.left)*ZOOM_COEFF - (borders.right - borders.left))/2;
    double zoom_y = ((borders.top - borders.bottom)*ZOOM_COEFF - (borders.top - borders.bottom))/2;
    // Zoom in / zoom out
    if(delta<0)
    {
        // TODO
        // Check for maximum values
        borders.right += zoom_x;
        borders.left -= zoom_x;
        borders.top += zoom_y;
        borders.bottom -= zoom_y;
    }
    else
    {
        // Ignore scaling if the margin is too small
        if((borders.right - borders.left<MIN_MARGIN)
           ||(borders.top - borders.bottom<MIN_MARGIN))
            return;

        borders.right -= zoom_x;
        borders.left += zoom_x;
        borders.top -= zoom_y;
        borders.bottom += zoom_y;
    }
    // Calibrate screen position to mouse pointer
    // I.e. scaling has to be performed closer to the current mouse pointer position
    double current_x = static_cast<double>(event.GetX());
    double current_y = static_cast<double>(event.GetY());
    TransformCoordinatesToGlobal(current_x, current_y);
    double delta_x = current_x - coordinates.x;
    double delta_y = current_y - coordinates.y;
    borders.right -= delta_x;
    borders.left -= delta_x;
    borders.top -= delta_y;
    borders.bottom -= delta_y;
    CalculateBestSnapRadius();
    this->Refresh();
}

void ViewPanel::OnResize(wxSizeEvent &event)
{
    int width, height;
    this->GetSize(&width, &height);
    // Keep right proportions for a drafting
    double scr_ratio = static_cast<double>(height)/ static_cast<double>(width);
    if(scr_ratio<=1)
        borders.right = borders.left + (borders.top - borders.bottom)/scr_ratio;
    else
        borders.bottom = borders.top - scr_ratio*(borders.right - borders.left);

    CalculateBestSnapRadius();
    this->Refresh();
}

void ViewPanel::CalculateBestSnapRadius()
{
    double dummy_y1 = 0;
    double dummy_y2 = 0;
    double dummy_x1 = 0;
    double dummy_x2 = 5;
    TransformCoordinatesToGlobal(dummy_x1, dummy_y1);
    TransformCoordinatesToGlobal(dummy_x2, dummy_y2);
    snap_radius = dummy_x2 - dummy_x1;
}

void ViewPanel::OnPaint(wxPaintEvent &event)
{
    wxAdapterDC dc(this, this->GetSize());
    dc.Clear();
    dc.SetBorders(borders.left, borders.right, borders.top, borders.bottom);
    draw_manager.DrawAll(dc);
    if(canvas_state!=STATE_NOTHING)
        draw_manager.ShowSnapPoints(dc, coordinates.x, coordinates.y, snap_radius);
    if(shape_builder)
        shape_builder->Redraw(dc, coordinates.x, coordinates.y);

    wxString debug_coord;
    debug_coord<<coordinates.x<<" - "<<coordinates.y<<" - "<<canvas_state;
    dc.SetTextForeground(wxColour(255,255,0));
    dc.DrawText(debug_coord, 100, 100);
}

void ViewPanel::SetCenterPosition(Point point)
{
    m_center_coordinate = point;
}


void ViewPanel::CreateEntityByPoints(AbstractBuilder *builder)
{
    canvas_state = STATE_PICKING_POINTS;
    // Reassign builder
    if(shape_builder!=nullptr)
        delete shape_builder;
    shape_builder = builder;
}

void ViewPanel::SetCenterPosition(double x, double y)
{
    m_center_coordinate.SetX(x);
    m_center_coordinate.SetY(y);
    m_center_coordinate.SetZ(0);
}

void ViewPanel::SetScreenSize(double width, double height)
{
    m_draft_width = width;
    m_draft_height = height;
}

Point ViewPanel::GetCenterPosition(void) const
{
    return m_center_coordinate;
}


void ViewPanel::TransformCoordinatesToGlobal(double &x, double &y)
{
    int width, height;
    this->GetSize(&width, &height);
    x = borders.left + x/static_cast<double>(width)*(borders.right - borders.left);
    y = borders.bottom + (static_cast<double>(height) - y)/static_cast<double>(height)*(borders.top - borders.bottom);
}

//void ViewPanel::TransformCoordinatesFromGlobal(double &x, double &y)
//{
//    int width, height;
//    this->GetSize(&width, &height);
//    x = borders.left + (borders.right - borders.left)*x/width;
//}

void ViewPanel::SetBorders(double left, double right, double top, double bottom)
{
    if((left>=right)||(bottom>=top))
        return;

    borders.left = left;
    borders.right = right;
    borders.top = top;
    borders.bottom = bottom;
    this->Refresh();
}

void ViewPanel::CancelCommand()
{
    canvas_state = STATE_NOTHING;
    if(shape_builder)
    {
        delete shape_builder;
        shape_builder = nullptr;
    }
    this->Refresh();
}

void ViewPanel::AddTestShapes()
{
    //    draw_manager.AddEntity(new Point(35,35));
//    draw_manager.AddEntity(new Point(37,37));
//    draw_manager.AddEntity(new Line(0, 0, 0, 100));
//    draw_manager.AddEntity(new Line(0,100,100, 100));
//    draw_manager.AddEntity(new Line(100,100,100, 0));
//    draw_manager.AddEntity(new Line(100,0,0, 0));
    //draw_manager.AddEntity(new Circle(0, 0, 10));
    draw_manager.AddEntity(new Square(Point(0,0),20,10));
    draw_manager.AddEntity(new Point(30,30));
    draw_manager.AddEntity(new Point(40,40));
}
