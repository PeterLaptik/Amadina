#ifndef WX_OCCT_PANEL_BASE_INCLUDED_H
#define WX_OCCT_PANEL_BASE_INCLUDED_H

#include <wx/panel.h>
#include <V3d_Viewer.hxx>
#include <V3d_View.hxx>
#include <AIS_ViewCube.hxx>
#include <OpenGl_GraphicDriver.hxx>
//#include <AIS_ViewController.hxx>

#ifdef _WIN32
#include <WNT_Window.hxx>
#endif
#ifdef __FreeBSD__
#include <Xw_Window.hxx>
#endif

#ifdef _WIN32
typedef Handle_WNT_Window Handle_Window_t;
#endif
#ifdef __FreeBSD__
typedef Handle(Xw_Window) Handle_Window_t;
#endif

class wxOccPanelBase : public wxPanel
{
    public:
        ///\brief Constructor
        ///\param parent - parent window
        ///\param pos - default panel position
        ///\param size - panel size
        ///\param style - panel style (see wxWidgets documentation)
        ///\param name - panel name
        wxOccPanelBase(wxWindow *parent,
            wxWindowID winid = wxID_ANY,
            const wxPoint &pos = wxDefaultPosition,
            const wxSize &size = wxDefaultSize,
            long style = wxTAB_TRAVERSAL | wxNO_BORDER,
            const wxString &name = wxPanelNameStr);

        ~wxOccPanelBase() override;


        void ShowGrid(bool show = true);
        bool IsGridShown(void) const;
        void DeleteSelected(void);


    protected:
        //TCollection_ExtendedString m_panel_name;
        Handle(Aspect_DisplayConnection) m_display_connection;
        Handle(OpenGl_GraphicDriver) m_graphic_driver;
        Handle_Window_t m_window;
        Handle(V3d_Viewer) m_viewer;
        Handle(V3d_View) m_view;
        //Handle(AIS_InteractiveContext) m_context;
        Handle(AIS_ViewCube) m_view_cube;
#ifdef __FreeBSD__
        bool m_is_initialized = false;
#endif

    DECLARE_EVENT_TABLE()
};

#endif
