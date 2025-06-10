#include "wxocctpanel_base.h"
//#include "wxoccpanel_styles.h"
//#include <BRepPrimAPI_MakeCylinder.hxx>
//#include <AIS_Line.hxx>
//#include <AIS_Point.hxx>
//#include <Geom_CartesianPoint.hxx>

#ifdef __FreeBSD__
#include <X11/Xlib.h>
#include <gtk/gtk.h>
#include <gdk/gdkx.h>
#include <gtk/gtkwidget.h>
#endif


const char *DEFAULT_NAME = "wxOCCPanel";

wxOccPanelBase::wxOccPanelBase(wxWindow *parent,
    wxWindowID winid,
    const wxPoint &pos,
    const wxSize &size,
    long style,
    const wxString &name)
    : wxPanel(parent, winid, pos, size, style, name)
{
#ifdef _WIN32
    HWND wnd = this->GetHandle();
    m_display_connection = new Aspect_DisplayConnection();
    m_graphic_driver = new OpenGl_GraphicDriver(m_display_connection);
    m_window = new WNT_Window((Aspect_Handle)wnd);

    m_viewer = new V3d_Viewer(m_graphic_driver); // manages views
    m_view = m_viewer->CreateView(); // orientation, mapping etc of an actual display
    m_view->SetWindow(m_window); // attach the view to the window
    if (!m_window->IsMapped())
        m_window->Map();

    //m_context = new AIS_InteractiveContext(m_viewer);

    m_viewer->SetDefaultLights();
    m_viewer->SetLightOn();
    m_view->SetBgGradientColors(Quantity_NOC_BLUE4, Quantity_NOC_GRAY80,
        Aspect_GradientFillMethod_Vertical);
    m_view->MustBeResized();

    //m_context->DisplayAll(true);
    m_view->Redraw();

    SetDefaultStyle();
    CreateViewCube();

#endif // _WIN32
}

wxOccPanelBase::~wxOccPanelBase()
{
    //delete m_floating_input;
}

void wxOccPanelBase::Init()
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

    //m_window = new Xw_Window(m_display_connection,"test", 20,20,400,400);
    m_window = new Xw_Window(m_display_connection, wid);

    m_viewer = new V3d_Viewer(m_graphic_driver);
    m_view = m_viewer->CreateView();
    m_view->SetWindow(m_window);
    if (!m_window->IsMapped())
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

void wxOccPanelBase::SetDefaultStyle()
{
    m_context->DefaultDrawer()->SetFaceBoundaryDraw(true);
    m_context->DefaultDrawer()->ShadingAspect()->SetColor(Quantity_NOC_GRAY70);
    m_context->DefaultDrawer()->LineAspect()->SetColor(Quantity_NOC_BLUE);
    m_context->DefaultDrawer()->LineAspect()->SetWidth(1.5);
    m_context->DefaultDrawer()->FaceBoundaryAspect()->SetColor(Quantity_NOC_BLACK);
    m_context->DefaultDrawer()->FaceBoundaryAspect()->SetWidth(1.0);
}

//void wxOccPanel::ClearAll()
//{
//    m_context->RemoveAll(true);
//    m_context->Display(m_view_cube, true);
//}

//void wxOccPanel::AddShape(Handle(AIS_InteractiveObject) shape)
//{
//    if (!shape)
//        return;
//
//// TODO comment
//#ifdef __FREEBSD__
//    if(!m_is_initialized)
//    {
//        return;
//    }
//#endif // __FREEBSD__
//
//    m_context->Display(shape, AIS_Shaded, 0, true);
//    m_context->DisplayAll(true);
//    m_view->Redraw();
//}

//void wxOccPanel::RemoveShape(Handle(AIS_InteractiveObject) shape)
//{
//    m_context->Remove(shape, true);
//    m_view->Redraw();
//}
//
//bool wxOccPanel::ContainsShapes(const std::vector<Handle(AIS_InteractiveObject)> &objects)
//{
//    int count_displayed = 0;
//    for (auto object : objects)
//    {
//        if(m_context->IsDisplayed(object))
//            ++count_displayed;
//    }
//    return count_displayed == objects.size();
//}

void wxOccPanelBase::DeleteSelected()
{

}

void wxOccPanelBase::OnPaint(wxPaintEvent &event)
{
#ifdef __FREEBSD__
    if (!m_is_initialized)
    {
        m_is_initialized = true;
        Init();
    }
#endif // __FREEBSD__

    m_view->Redraw();
}

void wxOccPanelBase::OnResize(wxSizeEvent &event)
{
#ifdef __FREEBSD__
    if (m_is_initialized)
    {
        m_view->MustBeResized();
    }
#endif // __FREEBSD__

#ifdef _WIN32
    m_view->MustBeResized();
#endif // _WIN32
}

void wxOccPanelBase::Test()
{
    //m_context->Activate(TopAbs_FACE, Standard_True);
    //ShowGrid(!IsGridShown());
}

void wxOccPanelBase::ShowGrid(bool show)
{
    //    if(!show)
    //    {
    //        //m_viewer->DisplayPrivilegedPlane(false);
    //        m_viewer->DeactivateGrid();
    //        m_view->Redraw();
    //        return;
    //    }
    //    gp_Pnt pnt(0,0,50);
    //    gp_Dir dir(0, 0, 1);
    //    gp_Pln plane(pnt, dir);
    //
    //
    //    gp_Ax3 ax(plane.Location(), plane.Axis().Direction());
    //    m_viewer->SetPrivilegedPlane(ax);
    //    //m_viewer->DisplayPrivilegedPlane(true);
    //
    //    m_viewer->SetRectangularGridValues(0, 1, 10, 10, 0);
    //    m_viewer->SetRectangularGridGraphicValues(100, 100, 0);
    //    m_viewer->ActivateGrid(Aspect_GT_Rectangular, Aspect_GDM_Lines);
    //    m_view->Redraw();
}

void wxOccPanelBase::OnMouseWheel(wxMouseEvent &event)
{
    Graphic3d_Vec2i pos(event.GetX(), event.GetY());
    double param = static_cast<double>(event.GetWheelRotation()) / m_scale_factor;
    Aspect_ScrollDelta ascroll(pos, param, Aspect_VKeyFlags_NONE);
    AIS_ViewController::UpdateMouseScroll(ascroll);
    AIS_ViewController::FlushViewEvents(m_context, m_view, true);
}

void wxOccPanelBase::OnLeftMouseButtonDown(wxMouseEvent &event)
{
    m_mouse_lb_clicked = true;
    Graphic3d_Vec2i pos(event.GetX(), event.GetY());
    Aspect_VKeyFlags flags = GetPressedKey();
    AIS_ViewController::PressMouseButton(pos, Aspect_VKeyMouse_LeftButton,
        flags, true);
}

//#include <BRepBuilderAPI_MakeFace.hxx>
//#include <BRepAdaptor_Surface.hxx>
//#include <GeomAPI_ProjectPointOnSurf.hxx>
//#include <Aspect_Grid.hxx>
void wxOccPanelBase::OnRightMouseButtonDown(wxMouseEvent &event)
{
    /*
    Graphic3d_Vec2i pos(event.GetX(), event.GetY());
    Standard_Real x, y, z;//, vx, vy, vz;
    //m_view->ConvertToGrid(event.GetX(), event.GetY(), x, y, z);
    //m_view->Proj(vx, vy, vz);
    //m_view->ConvertWithProj(event.GetX(), event.GetY(), x, y, z, vx, vy, vz);
    m_view->ConvertToGrid(event.GetX(), event.GetY(), x, y, z);


    // Default plane
    gp_Pnt pnt(0,0,0);
    gp_Dir dir(0, 0, 1);
    gp_Pln plane(pnt, dir);

    // Eye
    Standard_Real ex, ey, ez;
    m_view->At(ex, ey, ez);

    wxString tmp = "EYE: ";
    tmp<<"x = "<<ex<<", y = "<<ey<<", z = "<<ez;
    //wxMessageBox(tmp);

    TopoDS_Face face = BRepBuilderAPI_MakeFace(m_viewer->PrivilegedPlane());
    BRepAdaptor_Surface surface(face);
    const GeomAdaptor_Surface& geomAdapSurf = surface.Surface();
    const Handle(Geom_Surface)& geomSurf = geomAdapSurf.Surface();

    gp_Pnt picked = gp_Pnt(x, y, z);
    GeomAPI_ProjectPointOnSurf prj(picked, geomSurf);
    Standard_Integer index = prj.NbPoints();
    gp_Pnt ResultPoint = prj.Point(index);


    if(m_context->HasDetected() && m_context->MainSelector()->NbPicked()>0)
    {
        auto x = m_context->MainSelector()->OnePicked();
        Graphic3d_Vec2i pos(event.GetX(), event.GetY());
        //wxMessageBox("QQQQ");
    }

    Handle(Geom_Point) cpoint1 = new Geom_CartesianPoint(10, 5, 0);
    //Handle(Geom_Point) cpoint1 = new Geom_CartesianPoint(ResultPoint.X(), ResultPoint.Y(), ResultPoint.Z());
    Handle(AIS_Point) point1 = new AIS_Point(cpoint1);
    Handle(Geom_Point) cpoint2 = new Geom_CartesianPoint(0,0,0);
    Handle(AIS_Point) point2 = new AIS_Point(cpoint2);
    Handle(AIS_Line) line = new AIS_Line(cpoint1, cpoint2);
    //AddShape(line);
    */
}

void wxOccPanelBase::OnLeftMouseButtonUp(wxMouseEvent &event)
{
    m_mouse_lb_clicked = false;
    Graphic3d_Vec2i pos(event.GetX(), event.GetY());
    Aspect_VKeyFlags flags = GetPressedKey();
    AIS_ViewController::ReleaseMouseButton(pos, Aspect_VKeyMouse_LeftButton,
        flags, true);
}

//#include <Geom_Plane.hxx>
//#include <Geom_Line.hxx>
//#include <ElSLib.hxx>
//#include <GeomAPI_IntCS.hxx>
//#include <GC_MakeLine.hxx>
void wxOccPanelBase::OnMouseMove(wxMouseEvent &event)
{
    Graphic3d_Vec2i pos(event.GetX(), event.GetY());
    Aspect_VKeyMouse buttons = GetMouseButton(event);
    Aspect_VKeyFlags flags = GetPressedKey();

    AIS_ViewController::UpdateMousePosition(pos, buttons, flags, false);
    AIS_ViewController::FlushViewEvents(m_context, m_view, true);

    /*
    Standard_Real x, y, z, vx, vy, vz;
    Standard_Real px, py, pz;
    //m_view->ConvertToGrid(event.GetX(), event.GetY(), x, y, z);
    m_view->ConvertWithProj(event.GetX(), event.GetY(), x, y, z, vx, vy, vz);
    m_view->Proj(px, py, pz);
    if(tmp_line.get()!=nullptr)
        m_context->Remove(tmp_line, true);


    Handle(Geom_Surface) theSurf = new Geom_Plane(m_plane.Location(), m_plane.Axis().Direction());

    GeomAdaptor_Surface surface(theSurf);
    const GeomAdaptor_Surface& geomAdapSurf = surface.Surface();
    const Handle(Geom_Surface)& geomSurf = geomAdapSurf.Surface();

    Standard_Real ex, ey, ez;
    m_view->At(ex, ey, ez);

    //Standard_Real cosa, cosb, cosc, sum;

    gp_Pnt picked(x, y, z);
    GeomAPI_ProjectPointOnSurf prj(picked, geomSurf);
    Standard_Integer index = prj.NbPoints();
    gp_Pnt ResultPoint = prj.Point(index);


    Handle(Geom_Point) cpoint1 = new Geom_CartesianPoint(ResultPoint.X(), ResultPoint.Y(), ResultPoint.Z());
    Handle(AIS_Point) point1 = new AIS_Point(cpoint1);
    Handle(Geom_Point) cpoint2 = new Geom_CartesianPoint(0,0,0);
    Handle(AIS_Point) point2 = new AIS_Point(cpoint2);
    tmp_line = new AIS_Line(cpoint1, cpoint2);
    AddShape(tmp_line);

    MoveInterractor(event);
    */
}

void wxOccPanelBase::MoveInterractor(wxMouseEvent &event)
{
    /* if(m_floating_input==nullptr)
         return;

     m_floating_input->MoveTo(event.GetX(), event.GetY());
     Update();*/
}

gp_Pnt wxOccPanel::GetIntersectionPoint(int mouse_x, int mouse_y)
{
    //    gp_Pnt intersection_point;
    //    const gp_Dir direction = m_plane.Axis().Direction();
    //    Standard_Real A = direction.X();
    //    Standard_Real B = direction.Y();
    //    Standard_Real C = direction.Z();
    //    return intersection_point;
}

void wxOccPanelBase::CreateViewCube()
{
    m_view_cube = new AIS_ViewCube;
    m_view_cube->SetBoxColor(Quantity_NOC_GRAY80);
    m_view_cube->SetDrawAxes(true);
    m_view_cube->SetSize(40);
    m_view_cube->SetFontHeight(12);
    /*
    m_view_cube->SetTransformPersistence(
        new Graphic3d_TransformPers(
            Graphic3d_TMF_TriedronPers,
            Aspect_TOTP_LEFT_UPPER,
            Graphic3d_Vec2i(85, 85)));
    */
    m_context->Display(m_view_cube, false);
}

Aspect_VKeyMouse wxOccPanelBase::GetMouseButton(wxMouseEvent &event) const
{
    int button = event.GetButton();
    switch (button)
    {
        case wxMOUSE_BTN_LEFT:
            return Aspect_VKeyMouse_LeftButton;
        case wxMOUSE_BTN_RIGHT:
            return Aspect_VKeyMouse_RightButton;
    }
    return Aspect_VKeyMouse_NONE;
}

Aspect_VKeyFlags wxOccPanelBase::GetPressedKey() const
{
    if (wxGetKeyState(WXK_RAW_CONTROL))
        return Aspect_VKeyFlags_CTRL;
    else if (wxGetKeyState(WXK_SHIFT))
        return Aspect_VKeyFlags_SHIFT;
    else if (wxGetKeyState(WXK_ALT))
        return Aspect_VKeyFlags_ALT;

    return Aspect_VKeyFlags_NONE;
}

bool wxOccPanelBase::IsGridShown() const
{
    return m_viewer->IsGridActive();
}

//void wxOccPanel::SetScreenMode(ScreenMode mode)
//{
////    m_mode = mode;
//    // Ignore rotation on sketch mode
//    //SetAllowRotation(m_mode!=ScreenMode::SCREEN_SKETCHING);
//}
//
//ScreenMode wxOccPanel::GetScreenMode(void) const
//{
//    return m_mode;
//}
