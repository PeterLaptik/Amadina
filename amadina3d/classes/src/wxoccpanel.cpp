#include "../include/wxoccpanel.h"
#include <BRepPrimAPI_MakeCylinder.hxx>


const double SCALE_FACTOR = 1.1;
const char *DEFAULT_NAME = "wxOCCPanel";

wxBEGIN_EVENT_TABLE(wxOccPanel, wxPanel)
    EVT_PAINT(wxOccPanel::OnPaint)
    EVT_SIZE(wxOccPanel::OnResize)
    EVT_MOTION(wxOccPanel::OnMouseMove)
    EVT_MOUSEWHEEL(wxOccPanel::OnMouseWheel)
    EVT_LEFT_DOWN(wxOccPanel::OnMouseLeftButtonDown)
    EVT_LEFT_UP(wxOccPanel::OnMouseLeftButtonUp)
wxEND_EVENT_TABLE()

wxOccPanel::wxOccPanel(wxWindow *parent,
                     wxWindowID winid,
                    const wxPoint &pos,
                    const wxSize &size,
                    long style,
                    const wxString &name)
            : wxPanel(parent, winid, pos, size, style, name),
            m_scale_factor(SCALE_FACTOR),
            m_mouse_lb_clicked(false),
            m_last_x(-1), m_last_y(-1),
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

    m_view->SetBackgroundColor(Quantity_NOC_DARKSLATEGRAY4);
    m_view->MustBeResized();
    m_view->TriedronDisplay(Aspect_TOTP_LEFT_LOWER, Quantity_NOC_GOLD, 0.1, V3d_ZBUFFER);

    BRepPrimAPI_MakeCylinder cylinder(10., 50.);
    const TopoDS_Shape &shape = cylinder.Shape();
    aisthing = new AIS_Shape(shape);
    m_context->Display(aisthing, AIS_Shaded, 0, true);

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

void wxOccPanel::OnResize(wxSizeEvent &event)
{
    m_view->MustBeResized();
}

void wxOccPanel::OnMouseWheel(wxMouseEvent &event)
{
    int zoom = event.GetWheelRotation();
    Standard_Real scale = m_view->Scale();

    if(zoom<0)
        scale /= SCALE_FACTOR;
    else if(zoom>0)
        scale *= SCALE_FACTOR;

    m_view->SetScale(scale);
}

void wxOccPanel::OnMouseLeftButtonDown(wxMouseEvent &event)
{
    m_mouse_lb_clicked = true;
}

void wxOccPanel::OnMouseLeftButtonUp(wxMouseEvent &event)
{
    m_mouse_lb_clicked = false;
}

void wxOccPanel::OnMouseMove(wxMouseEvent &event)
{
    int x = event.GetX();
    int y = event.GetY();
    if(m_mouse_lb_clicked)
    {
        if(m_last_x<0 || m_last_y<0)
        {
            m_last_x = x;
            m_last_y = y;
            return;
        }

        int dx = m_last_x - x;
        int dy = m_last_y - y;
        m_view->Move(dx, dy, 0, Standard_True);
    }
}
