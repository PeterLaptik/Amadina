#include "wxoccpanel.h"

#ifdef __FreeBSD__
#include <X11/Xlib.h>
#include <gtk/gtk.h>
#include <gdk/gdkx.h>
#include <gtk/gtkwidget.h>
#endif

// Nominal mouse wheel amount for one click (known as a 'detent')
// See description in MSDN
const double WHEEL_DELTA = 120.0;

const char *DEFAULT_NAME = "wxOCCPanel";

wxBEGIN_EVENT_TABLE(wxOccPanel, wxPanel)
    EVT_PAINT(wxOccPanel::OnPaint)
    EVT_SIZE(wxOccPanel::OnResize)
    EVT_MOTION(wxOccPanel::OnMouseMove)
    EVT_MOUSEWHEEL(wxOccPanel::OnMouseWheel)
    EVT_LEFT_DOWN(wxOccPanel::OnLeftMouseButtonDown)
    EVT_LEFT_UP(wxOccPanel::OnLeftMouseButtonUp)
    EVT_RIGHT_DOWN(wxOccPanel::OnRightMouseButtonDown)
wxEND_EVENT_TABLE()


wxOccPanel::wxOccPanel(wxWindow *parent,
                       wxWindowID winid,
                       const wxPoint &pos,
                       const wxSize &size,
                       long style,
                       const wxString &name)
    : wxPanel(parent, winid, pos, size, style, name),
      m_scale_factor(WHEEL_DELTA)
{
#ifdef _WIN32
    HWND wnd = this->GetHandle();
    m_display_connection = new Aspect_DisplayConnection();
    m_graphic_driver = new OpenGl_GraphicDriver(m_display_connection);
    m_window = new WNT_Window((Aspect_Handle) wnd);

    m_viewer = new V3d_Viewer(m_graphic_driver);
    m_view = m_viewer->CreateView();
    m_view->SetWindow(m_window);
    if(!m_window->IsMapped())
        m_window->Map();

    m_context = new AIS_InteractiveContext(m_viewer);

    m_viewer->SetDefaultLights();
    m_viewer->SetLightOn();
    m_view->SetBgGradientColors(Quantity_NOC_BLUE4, Quantity_NOC_GRAY80,
                                Aspect_GradientFillMethod_Vertical);
    m_view->MustBeResized();

    m_context->DisplayAll(true);
    m_view->Redraw();

    SetDefaultStyle();
    CreateViewCube();

#endif // _WIN32
}

void wxOccPanel::Init()
{
#ifdef __FreeBSD__
    m_display_connection = new Aspect_DisplayConnection();
    m_graphic_driver = new OpenGl_GraphicDriver(m_display_connection);

    GtkWidget* widget = this->GetHandle();
    gtk_widget_realize(widget);
    gtk_widget_set_double_buffered(widget, 0);

    GdkWindow *gdk_window = gtk_widget_get_window(widget);
    Window wid = gdk_x11_window_get_xid(gdk_window);
    XSync(GDK_WINDOW_XDISPLAY(gdk_window), True);

    m_window = new Xw_Window(m_display_connection, wid);

    m_viewer = new V3d_Viewer(m_graphic_driver);
    m_view = m_viewer->CreateView();
    m_view->SetWindow(m_window);
    if(!m_window->IsMapped())
        m_window->Map();

    m_context = new AIS_InteractiveContext(m_viewer);

    m_view->MustBeResized();
    m_context->DisplayAll(true);
    m_view->Redraw();

    m_viewer->SetDefaultLights();
    m_viewer->SetLightOn();
    m_view->SetBgGradientColors(Quantity_NOC_BLUE4, Quantity_NOC_GRAY80,
                                Aspect_GradientFillMethod_Vertical);

    m_view->MustBeResized();
    m_context->SetDisplayMode(AIS_Shaded, Standard_True);

    SetDefaultStyle();
    CreateViewCube();
#endif // __FreeBSD__
}

void wxOccPanel::SetDefaultStyle()
{
    m_context->DefaultDrawer()->SetFaceBoundaryDraw(true);
    m_context->DefaultDrawer()->ShadingAspect()->SetColor(Quantity_NOC_GRAY70);
    m_context->DefaultDrawer()->LineAspect()->SetColor(Quantity_NOC_BLUE);
    m_context->DefaultDrawer()->LineAspect()->SetWidth(1.5);
    m_context->DefaultDrawer()->FaceBoundaryAspect()->SetColor(Quantity_NOC_BLACK);
    m_context->DefaultDrawer()->FaceBoundaryAspect()->SetWidth(1.0);
}

void wxOccPanel::OnPaint(wxPaintEvent &event)
{
#ifdef __FREEBSD__
    if(!m_is_initialized)
    {
        m_is_initialized = true;
        Init();
    }
#endif // __FREEBSD__
    m_view->Redraw();
}

void wxOccPanel::OnResize(wxSizeEvent &event)
{
#ifdef __FREEBSD__
    if(m_is_initialized)
    {
        m_view->MustBeResized();
    }
#endif // __FREEBSD__

#ifdef _WIN32
    m_view->MustBeResized();
#endif // _WIN32
}


void wxOccPanel::OnMouseWheel(wxMouseEvent &event)
{
    Graphic3d_Vec2i pos(event.GetX(), event.GetY());
    double param = static_cast<double>(event.GetWheelRotation())/m_scale_factor;
    Aspect_ScrollDelta ascroll(pos, param, Aspect_VKeyFlags_NONE);
    AIS_ViewController::UpdateMouseScroll(ascroll);
    AIS_ViewController::FlushViewEvents (m_context, m_view, true);
}

void wxOccPanel::OnLeftMouseButtonDown(wxMouseEvent &event)
{
    m_mouse_lb_clicked = true;
    Graphic3d_Vec2i pos(event.GetX(), event.GetY());
    Aspect_VKeyFlags flags = GetPressedKey();
    AIS_ViewController::PressMouseButton(pos, Aspect_VKeyMouse_LeftButton,
                                         flags, true);
}

void wxOccPanel::OnRightMouseButtonDown(wxMouseEvent &event)
{

}

void wxOccPanel::OnLeftMouseButtonUp(wxMouseEvent &event)
{
    m_mouse_lb_clicked = false;
    Graphic3d_Vec2i pos(event.GetX(), event.GetY());
    Aspect_VKeyFlags flags = GetPressedKey();
    AIS_ViewController::ReleaseMouseButton(pos, Aspect_VKeyMouse_LeftButton,
                                           flags, true);
}

void wxOccPanel::OnMouseMove(wxMouseEvent &event)
{
    Graphic3d_Vec2i pos(event.GetX(), event.GetY());
    Aspect_VKeyMouse buttons = GetMouseButton(event);
    Aspect_VKeyFlags flags = GetPressedKey();
    AIS_ViewController::UpdateMousePosition(pos, buttons, flags, false);
    AIS_ViewController::FlushViewEvents(m_context, m_view, true);
}

void wxOccPanel::CreateViewCube()
{
    m_view_cube = new AIS_ViewCube;
    m_view_cube->SetBoxColor(Quantity_NOC_GRAY80);
    m_view_cube->SetDrawAxes(true);
    m_view_cube->SetSize(40);
    m_view_cube->SetFontHeight(12);
    m_context->Display(m_view_cube, false);
    m_view->Redraw();
}

void wxOccPanel::RemoveViewCube()
{
    m_context->Remove(m_view_cube, true);
    m_view->Redraw();
}

Aspect_VKeyMouse wxOccPanel::GetMouseButton(wxMouseEvent &event) const
{
    int button = event.GetButton();
    switch(button)
    {
    case wxMOUSE_BTN_LEFT:
        return Aspect_VKeyMouse_LeftButton;
    case wxMOUSE_BTN_RIGHT:
        return Aspect_VKeyMouse_RightButton;
    }
    return Aspect_VKeyMouse_NONE;
}

Aspect_VKeyFlags wxOccPanel::GetPressedKey() const
{
    if(wxGetKeyState(WXK_RAW_CONTROL))
        return Aspect_VKeyFlags_CTRL;
    else if(wxGetKeyState(WXK_SHIFT))
        return Aspect_VKeyFlags_SHIFT;
    else if(wxGetKeyState(WXK_ALT))
        return Aspect_VKeyFlags_ALT;

    return Aspect_VKeyFlags_NONE;
}

Handle(Aspect_DisplayConnection) wxOccPanel::GetDisplayConnection()
{
    return m_display_connection;
}

Handle(OpenGl_GraphicDriver) wxOccPanel::GetGraphicDriver()
{
    return m_graphic_driver;
}

Handle_Window_t wxOccPanel::GetWindow()
{
    return m_window;
}

Handle(V3d_Viewer) wxOccPanel::GetViwer()
{
    return m_viewer;
}

Handle(V3d_View) wxOccPanel::GetView()
{
    return m_view;
}

Handle(AIS_InteractiveContext) wxOccPanel::GetContext()
{
    return m_context;
}

void wxOccPanel::HideViewCube()
{
    if (!is_view_cube_visible)
        return;

    is_view_cube_visible = false;
    RemoveViewCube();
}

void wxOccPanel::ShowViewCube()
{
    if (is_view_cube_visible)
        return;

    is_view_cube_visible = true;
    CreateViewCube();
}


