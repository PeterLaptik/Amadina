#ifndef WX_OCC_PANEL_INCLUDED_H
#define WX_OCC_PANEL_INCLUDED_H

#include <abstract_canvas.h>
#include <wx/panel.h>
#include <V3d_View.hxx>
#include <AIS_ViewController.hxx>
#include <V3d_Viewer.hxx>
#include <AIS_ViewCube.hxx>
#include <AIS_InteractiveContext.hxx>
#include <OpenGl_GraphicDriver.hxx>
#ifdef _WIN32
#include <WNT_Window.hxx>
#endif
#ifdef __FreeBSD__
#include <Xw_Window.hxx>
#endif

#ifdef _WINDLL
#define DLL_EXPORT __declspec(dllexport)
#else
#define DLL_EXPORT
#endif


#ifdef _WIN32
typedef Handle_WNT_Window Handle_Window_t;
#endif
#ifdef __FreeBSD__
typedef Handle(Xw_Window) Handle_Window_t;
#endif


class DLL_EXPORT wxOccPanel : public wxPanel, public AIS_ViewController, public cad::model::AbstractCanvas
{
    public:
        ///\brief Constructor
        ///\param parent - parent window
        ///\param pos - default panel position
        ///\param size - panel size
        ///\param style - panel style (see wxWidgets documentation)
        ///\param name - panel name
        wxOccPanel(wxWindow *parent,
                    wxWindowID winid = wxID_ANY,
                    const wxPoint &pos = wxDefaultPosition,
                    const wxSize &size = wxDefaultSize,
                    long style = wxTAB_TRAVERSAL | wxNO_BORDER,
                    const wxString &name = wxPanelNameStr);

        ~wxOccPanel() override = default;
        
        void HideViewCube();
        void ShowViewCube();

        Handle(Aspect_DisplayConnection) GetDisplayConnection();
        Handle(OpenGl_GraphicDriver) GetGraphicDriver();
        Handle_Window_t GetWindow();
        Handle(V3d_Viewer) GetViwer();
        Handle(V3d_View) GetView();
        Handle(AIS_InteractiveContext) GetContext();
        

    private:
        void Init();
        void SetDefaultStyle();
        Aspect_VKeyMouse GetMouseButton(wxMouseEvent &event) const;
        Aspect_VKeyFlags GetPressedKey(void) const;
        void CreateViewCube();
        void RemoveViewCube();


        void OnPaint(wxPaintEvent &event);
        void OnResize(wxSizeEvent &event);
        void OnMouseWheel(wxMouseEvent &event);
        void OnMouseMove(wxMouseEvent &event);
        void OnLeftMouseButtonDown(wxMouseEvent &event);
        void OnLeftMouseButtonUp(wxMouseEvent &event);
        void OnRightMouseButtonDown(wxMouseEvent &event);
    
        double m_scale_factor;
        bool m_mouse_lb_clicked = false;
        bool is_view_cube_visible = true;

        Handle(Aspect_DisplayConnection) m_display_connection;
        Handle(OpenGl_GraphicDriver) m_graphic_driver;
        Handle_Window_t m_window;
        Handle(V3d_Viewer) m_viewer;
        Handle(V3d_View) m_view;
        Handle(AIS_InteractiveContext) m_context;
        Handle(AIS_ViewCube) m_view_cube;
#ifdef __FreeBSD__
        bool m_is_initialized = false;
#endif

    DECLARE_EVENT_TABLE()
};

#endif // WX_OCC_PANEL_INCLUDED_H
