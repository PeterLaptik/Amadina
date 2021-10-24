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
    EVT_CHAR_HOOK(ViewPanel::OnKeyPressed)
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
    //m_screen_impl = new Screen();
    Screen::ScreenResize(width_px, height_px);
    wxPanel::SetBackgroundColour(wxColour(DEFAULT_COLOUR_VALUE, DEFAULT_COLOUR_VALUE, DEFAULT_COLOUR_VALUE));
    Screen::SetColour(Colour(DEFAULT_COLOUR_VALUE, DEFAULT_COLOUR_VALUE, DEFAULT_COLOUR_VALUE));
    // Test shapes
    #ifdef TEST_MODE
        AddTestShapes();
    #endif // TEST_MODE
}


void ViewPanel::OnKeyPressed(wxKeyEvent &event)
{
    // mock-method for wxWidgets-based panel
    // excludes UB on char hook event skipping in main frame
}


ViewPanel::~ViewPanel()
{
    //delete m_screen_impl;
}

void ViewPanel::OnMouseMove(wxMouseEvent &event)
{
    Screen::ScreenMouseMove(event.GetX(), event.GetY(),
                            wxGetKeyState(WXK_RAW_CONTROL),
                            wxGetMouseState().LeftIsDown());

}

void ViewPanel::OnMouseWheelDown(wxMouseEvent &event)
{
    Screen::ScreenMouseWheelDown(event.GetX(), event.GetY());
}

void ViewPanel::OnMouseWheelUp(wxMouseEvent &event)
{
    Screen::ScreenMouseWheelUp(event.GetX(), event.GetY());
}

void ViewPanel::OnMouseLeftButtonDown(wxMouseEvent &event)
{
    Screen::ScreenMouseLeftButtonClicked(event.GetX(), event.GetY(), wxGetKeyState(WXK_RAW_CONTROL));
}

void ViewPanel::OnMouseLeftButtonUp(wxMouseEvent &event)
{
    Screen::ScreenMouseLeftButtonUp(event.GetX(), event.GetY());
}

void ViewPanel::OnMouseWheel(wxMouseEvent &event)
{
    Screen::ScreenMouseWheel(event.GetWheelRotation(), event.GetX(), event.GetY());
}

void ViewPanel::OnResize(wxSizeEvent &event)
{
    int width, height;
    this->GetSize(&width, &height);
    Screen::ScreenResize(width, height);
}

void ViewPanel::OnPaint(wxPaintEvent &event)
{
    wxAdapterDC dc(this, this->GetSize());
    Screen::RedrawAll(dc);
}

void ViewPanel::CreateEntityByPoints(AbstractBuilder *builder)
{
    Screen::CreateEntity(builder);
}

void ViewPanel::CancelCommand()
{
    Screen::ScreenCancelCommand();
}

void ViewPanel::DeleteSelection()
{
    // TODO
    Screen::GetDrawManager()->DeleteSelection();
    this->Refresh();
}

DrawManager* ViewPanel::GetDrawManager(void)
{
    return Screen::GetDrawManager();
}

bool ViewPanel::SetBackgroundColour(const wxColour &colour)
{
    Screen::SetColour(Colour(colour.Red(), colour.Green(), colour.Blue()));
    return wxPanel::SetBackgroundColour(colour);
}

// Adds shapes for testing
void ViewPanel::AddTestShapes()
{
    Screen::GetDrawManager()->AddEntity(new Square(Point(0,0),20,10));
    Screen::GetDrawManager()->AddEntity(new Point(30,30));
    Screen::GetDrawManager()->AddEntity(new Point(40,40));
}

void ViewPanel::ScreenRefresh()
{
    this->Refresh();
}
