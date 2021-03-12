#include "viewpanel.h"
#include "../graphics/dcadapter_wx.h"
#include "../entities/line.h"
#include "../entities/circle.h"
#include "../entities/square.h"
#include <wx/dcclient.h>

#define TEST_MODE

// Default background colour value (red=green=blue)
static const int DEFAULT_COLOUR_VALUE = 80;


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
    shape_builder = nullptr;
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
    if(m_screen.ScreenMouseLeftButtonClicked(event.GetX(), event.GetY(), wxGetKeyState(WXK_RAW_CONTROL)))
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

void ViewPanel::OnPaint(wxPaintEvent &event)
{
    wxAdapterDC dc(this, this->GetSize());
    dc.Clear();
    m_screen.RedrawAll(dc);
}

void ViewPanel::CreateEntityByPoints(AbstractBuilder *builder)
{
    m_screen.CreateEntity(builder);
    this->Refresh();
}

void ViewPanel::SetScreenSize(double width, double height)
{
    m_draft_width = width;
    m_draft_height = height;
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
