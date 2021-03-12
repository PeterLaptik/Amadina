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

static const int DEFAULT_COLOUR_VALUE = 50;


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
    m_screen.ScreenResize(width_px, height_px);
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
    bool need_to_be_refreshed = m_screen.ScreenMouseMove(event.GetX(), event.GetY(),
                                            wxGetKeyState(WXK_RAW_CONTROL),
                                            wxGetMouseState().LeftIsDown());
    if(need_to_be_refreshed)
        this->Refresh();
}

void ViewPanel::OnMouseWheelDown(wxMouseEvent &event)
{
    m_screen.ScreenMouseWheelDown(event.GetX(), event.GetY());
}


void ViewPanel::OnMouseWheelUp(wxMouseEvent &event)
{
    m_screen.ScreenMouseWheelUp(event.GetX(), event.GetY());
}

void ViewPanel::OnMouseLeftButtonDown(wxMouseEvent &event)
{
    if(m_screen.ScreenMouseLBClicked(event.GetX(), event.GetY(), wxGetKeyState(WXK_RAW_CONTROL)))
        this->Refresh();
}

void ViewPanel::OnMouseLeftButtonUp(wxMouseEvent &event)
{
    m_screen.ScreenMouseLeftButtonUp(event.GetX(), event.GetY());
}

void ViewPanel::OnMouseWheel(wxMouseEvent &event)
{
    m_screen.ScreenMouseWheel(event.GetWheelRotation(), event.GetX(), event.GetY());
    this->Refresh();
}

void ViewPanel::OnResize(wxSizeEvent &event)
{
    int width, height;
    this->GetSize(&width, &height);
    m_screen.ScreenResize(width, height);
    this->Refresh();
}

//void ViewPanel::CalculateBestSnapRadius()
//{
//    double dummy_y1 = 0;
//    double dummy_y2 = 0;
//    double dummy_x1 = 0;
//    double dummy_x2 = 5;
//    TransformCoordinatesToGlobal(dummy_x1, dummy_y1);
//    TransformCoordinatesToGlobal(dummy_x2, dummy_y2);
//    snap_radius = dummy_x2 - dummy_x1;
//}

void ViewPanel::OnPaint(wxPaintEvent &event)
{
    wxAdapterDC dc(this, this->GetSize());
    dc.Clear();
    m_screen.RedrawAll(dc);
}

void ViewPanel::SetCenterPosition(Point point)
{
    m_center_coordinate = point;
}


void ViewPanel::CreateEntityByPoints(AbstractBuilder *builder)
{
    m_screen.CreateEntity(builder);
    this->Refresh();
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


//void ViewPanel::TransformCoordinatesToGlobal(double &x, double &y)
//{
//    int width, height;
//    this->GetSize(&width, &height);
//    x = borders.left + x/static_cast<double>(width)*(borders.right - borders.left);
//    y = borders.bottom + (static_cast<double>(height) - y)/static_cast<double>(height)*(borders.top - borders.bottom);
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
    m_screen.CancelCommand();
    this->Refresh();
}

void ViewPanel::DeleteSelection()
{
    m_screen.GetDrawManager()->DeleteSelection();
    this->Refresh();
}

void ViewPanel::AddTestShapes()
{
    m_screen.GetDrawManager()->AddEntity(new Square(Point(0,0),20,10));
    m_screen.GetDrawManager()->AddEntity(new Point(30,30));
    m_screen.GetDrawManager()->AddEntity(new Point(40,40));
}
