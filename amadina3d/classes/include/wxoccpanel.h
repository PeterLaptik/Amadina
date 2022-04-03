#ifndef WXOCCPANEL_H
#define WXOCCPANEL_H

#include <wx/panel.h>
//#include <BRepPrimAPI_MakeBox.hxx>
//#include <BRepPrimAPI_MakeCylinder.hxx>
#include <V3d_Viewer.hxx>
#include <WNT_Window.hxx>
#include <AIS_InteractiveContext.hxx>
//#include <Aspect_DisplayConnection.hxx>
#include <OpenGl_GraphicDriver.hxx>
#include <V3d_View.hxx>
//#include <AIS_Shape.hxx>

class wxOccPanel: public wxPanel
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

        virtual ~wxOccPanel();

    protected:
        void OnPaint(wxPaintEvent &event);

    private:
        TCollection_ExtendedString m_panel_name;
        Handle(Aspect_DisplayConnection) m_display_connection;
        Handle(OpenGl_GraphicDriver) m_graphic_driver;
        Handle_WNT_Window m_window;
        Handle(V3d_Viewer) m_viewer;
        Handle(V3d_View) m_view;
        Handle(AIS_InteractiveContext) m_context;

    DECLARE_EVENT_TABLE()
};

#endif // WXOCCPANEL_H
