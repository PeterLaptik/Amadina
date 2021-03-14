#include "viewpanel.h"
#include "screen.h"
#include "../graphics/dcadapter_wx.h"
#include "../entities/line.h"
#include "../entities/circle.h"
#include "../entities/square.h"
#include <wx/dcclient.h>

//#define TEST_MODE

// Default background colour value
// (red=green=blue) - for panel background colour
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
    int width_px;
    int height_px;
    this->GetSize(&width_px, &height_px);
    this->SetBackgroundStyle(wxBG_STYLE_PAINT);
    // Screen implementation initializing
    m_screen_impl = new Screen();
    m_screen_impl->ScreenResize(width_px, height_px);
    wxPanel::SetBackgroundColour(wxColour(DEFAULT_COLOUR_VALUE, DEFAULT_COLOUR_VALUE, DEFAULT_COLOUR_VALUE));
    m_screen_impl->SetColour(Colour(DEFAULT_COLOUR_VALUE, DEFAULT_COLOUR_VALUE, DEFAULT_COLOUR_VALUE));
    // Test shapes
    #ifdef TEST_MODE
        AddTestShapes();
    #endif // TEST_MODE
}

ViewPanel::~ViewPanel()
{
    delete m_screen_impl;
}

void ViewPanel::OnMouseMove(wxMouseEvent &event)
{
    bool need_to_be_refreshed = m_screen_impl->ScreenMouseMove(event.GetX(), event.GetY(),
                                            wxGetKeyState(WXK_RAW_CONTROL),
                                            wxGetMouseState().LeftIsDown());
    if(need_to_be_refreshed)
        this->Refresh();
}

void ViewPanel::OnMouseWheelDown(wxMouseEvent &event)
{
    m_screen_impl->ScreenMouseWheelDown(event.GetX(), event.GetY());
}

void ViewPanel::OnMouseWheelUp(wxMouseEvent &event)
{
    m_screen_impl->ScreenMouseWheelUp(event.GetX(), event.GetY());
}

void ViewPanel::OnMouseLeftButtonDown(wxMouseEvent &event)
{
    if(m_screen_impl->ScreenMouseLeftButtonClicked(event.GetX(), event.GetY(), wxGetKeyState(WXK_RAW_CONTROL)))
        this->Refresh();
}

void ViewPanel::OnMouseLeftButtonUp(wxMouseEvent &event)
{
    m_screen_impl->ScreenMouseLeftButtonUp(event.GetX(), event.GetY());
}

void ViewPanel::OnMouseWheel(wxMouseEvent &event)
{
    m_screen_impl->ScreenMouseWheel(event.GetWheelRotation(), event.GetX(), event.GetY());
    this->Refresh();
}

void ViewPanel::OnResize(wxSizeEvent &event)
{
    int width, height;
    this->GetSize(&width, &height);
    m_screen_impl->ScreenResize(width, height);
    this->Refresh();
}

void ViewPanel::OnPaint(wxPaintEvent &event)
{
    wxAdapterDC dc(this, this->GetSize());
    m_screen_impl->RedrawAll(dc);
}

void ViewPanel::CreateEntityByPoints(AbstractBuilder *builder)
{
    m_screen_impl->CreateEntity(builder);
    this->Refresh();
}

void ViewPanel::CancelCommand()
{
    m_screen_impl->CancelCommand();
    this->Refresh();
}

void ViewPanel::DeleteSelection()
{
    m_screen_impl->GetDrawManager()->DeleteSelection();
    this->Refresh();
}

DrawManager* ViewPanel::GetDrawManager(void)
{
    return m_screen_impl->GetDrawManager();
}

bool ViewPanel::SetBackgroundColour(const wxColour &colour)
{
    m_screen_impl->SetColour(Colour(colour.Red(), colour.Green(), colour.Blue()));
    return wxPanel::SetBackgroundColour(colour);
}

// Adds shapes for testing
void ViewPanel::AddTestShapes()
{
    m_screen_impl->GetDrawManager()->AddEntity(new Square(Point(0,0),20,10));
    m_screen_impl->GetDrawManager()->AddEntity(new Point(30,30));
    m_screen_impl->GetDrawManager()->AddEntity(new Point(40,40));
}
