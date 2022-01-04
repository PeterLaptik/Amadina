#include "viewpanel.h"
#include "events.h"
#include "dcadapter_wx.h"
#include <wx/dcclient.h>
#include <thread>
// Kernel dependencies:
#include "view_2d/screen.h"
#include "entities/line.h"
#include "entities/circle.h"
#include "entities/square.h"
#include "command/command.h"

// Default background colour value
// (red=green=blue) - for panel background colour
static const int DEFAULT_COLOUR_VALUE = 0;

wxDEFINE_EVENT(wxCAD_PANEL_MOVE, MouseMoveEvent);

wxBEGIN_EVENT_TABLE(ViewPanel, wxPanel)
    EVT_PAINT(ViewPanel::OnPaint)
    EVT_SIZE(ViewPanel::OnResize)
    EVT_LEFT_DOWN(ViewPanel::OnMouseLeftButtonDown)
    EVT_LEFT_UP(ViewPanel::OnMouseLeftButtonUp)
    EVT_MOTION(ViewPanel::OnMouseMove)
    EVT_MOUSEWHEEL(ViewPanel::OnMouseWheel)
    EVT_MIDDLE_DOWN(ViewPanel::OnMouseWheelDown)
    EVT_MIDDLE_UP(ViewPanel::OnMouseWheelUp)
    EVT_ENTER_WINDOW(ViewPanel::OnMouseEnterPanel)
    EVT_LEAVE_WINDOW(ViewPanel::OnMouseLeavePanel)
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
    Screen::ScreenResize(width_px, height_px);
    wxPanel::SetBackgroundColour(wxColour(DEFAULT_COLOUR_VALUE, DEFAULT_COLOUR_VALUE, DEFAULT_COLOUR_VALUE));
    Screen::SetColour(Colour(DEFAULT_COLOUR_VALUE, DEFAULT_COLOUR_VALUE, DEFAULT_COLOUR_VALUE));
}

ViewPanel::~ViewPanel()
{
    //delete m_screen_impl;
}

// TODO
int coord_x, coord_y;

void ViewPanel::OnMouseMove(wxMouseEvent &event)
{
    coord_x = event.GetX();
    coord_y = event.GetY();
    Screen::ScreenMouseMove(event.GetX(), event.GetY(),
                            wxGetKeyState(WXK_RAW_CONTROL),
                            wxGetMouseState().LeftIsDown());
    wxPostEvent(this, MouseMoveEvent(wxCAD_PANEL_MOVE));
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

void ViewPanel::ScreenKeyPressed(char key)
{
    Screen::ScreenKeyPressed(key);
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
    ShowCursor(dc);
}

static const int SIZE_SQUARE = 5;

void ViewPanel::ShowCursor(wxDC &dc)
{
    InteractiveState state = Screen::GetState();
    dc.SetPen(wxPen(GetColour().IsDark() ? *wxWHITE : *wxBLACK));

    switch (state)
    {
        case SCR_PICKING:
            dc.DrawLine(coord_x-20, coord_y, coord_x+20, coord_y);
            dc.DrawLine(coord_x, coord_y-20, coord_x, coord_y+20);
            break;
        case SCR_SELECTING:
            dc.DrawLine(coord_x-SIZE_SQUARE, coord_y-SIZE_SQUARE,
                        coord_x-SIZE_SQUARE, coord_y+SIZE_SQUARE);
            dc.DrawLine(coord_x+SIZE_SQUARE, coord_y+SIZE_SQUARE,
                        coord_x-SIZE_SQUARE, coord_y+SIZE_SQUARE);
            dc.DrawLine(coord_x+SIZE_SQUARE, coord_y+SIZE_SQUARE,
                        coord_x+SIZE_SQUARE, coord_y-SIZE_SQUARE);
            dc.DrawLine(coord_x-SIZE_SQUARE, coord_y-SIZE_SQUARE,
                        coord_x+SIZE_SQUARE, coord_y-SIZE_SQUARE);
            break;
    }
}


bool ViewPanel::SetBackgroundColour(const wxColour &colour)
{
    Screen::SetColour(Colour(colour.Red(), colour.Green(), colour.Blue()));
    return wxPanel::SetBackgroundColour(colour);
}


void ViewPanel::ClearSelection()
{
    Screen::ClearSelection();
}

const std::vector<Entity*>& ViewPanel::GetSelection(void)
{
    return Screen::GetSelection();
}

void ViewPanel::OnMouseEnterPanel(wxMouseEvent &event)
{
    // TODO: hide cursor
    //SetCursor(wxCursor(*wxHOURGLASS_CURSOR));
}

void ViewPanel::OnMouseLeavePanel(wxMouseEvent &event)
{

}

void ViewPanel::RefreshScreen()
{
    this->Refresh();
}
