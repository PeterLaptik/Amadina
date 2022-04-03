#include "../include/wxoccpanel.h"

const char *DEFAULT_NAME = "wxOCCPanel";

wxBEGIN_EVENT_TABLE(wxOccPanel, wxPanel)
    EVT_PAINT(wxOccPanel::OnPaint)
wxEND_EVENT_TABLE()

wxOccPanel::wxOccPanel(wxWindow *parent,
                     wxWindowID winid,
                    const wxPoint &pos,
                    const wxSize &size,
                    long style,
                    const wxString &name)
            : wxPanel(parent, winid, pos, size, style, name),
            m_panel_name(DEFAULT_NAME)
{
    HWND wnd = this->GetHandle();
    m_display_connection = new Aspect_DisplayConnection();
    m_graphic_driver = new OpenGl_GraphicDriver(m_display_connection);
    m_window = new WNT_Window((Aspect_Handle) wnd);

    m_viewer = new V3d_Viewer(m_graphic_driver); // manages views
    // view is the orientation, mapping etc of your actual display
    m_view = m_viewer->CreateView();
    // attach the view to the window
    m_view->SetWindow(m_window);
    if(!m_window->IsMapped())
        m_window->Map();
    // for selection management i.e neutral point or open local context
    m_context = new AIS_InteractiveContext(m_viewer);
    // makes everything come alive
    m_viewer->SetDefaultLights();
    // makes everything come alive
    m_viewer->SetLightOn();

    m_view->SetBackgroundColor(Quantity_NOC_GRAY11);
    m_view->MustBeResized();
    m_view->TriedronDisplay(Aspect_TOTP_LEFT_LOWER, Quantity_NOC_GOLD, 0.08, V3d_ZBUFFER);

//    aisthing = new AIS_Shape(shape);
//    context->Display(aisthing, true);
    m_context->DisplayAll(true);
    m_view->Redraw();
}

wxOccPanel::~wxOccPanel()
{

}

void wxOccPanel::OnPaint(wxPaintEvent &event)
{
    m_view->Redraw();
}
