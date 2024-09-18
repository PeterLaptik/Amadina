#ifndef WXOCCPANEL_H
#define WXOCCPANEL_H

#include "objectpool.h"
#include "abstract_shape.h"
#include "occt_canvas.h"
#include "screen_modes.h"
#include <wx/panel.h>
#include <AIS_ViewController.hxx>
#include <V3d_Viewer.hxx>
#include <WNT_Window.hxx>
#include <AIS_InteractiveContext.hxx>
#include <OpenGl_GraphicDriver.hxx>
#include <V3d_View.hxx>
#include <AIS_Shape.hxx>
#include <AIS_ViewCube.hxx>
#include <AIS_Line.hxx>

using cad::modeller::AbstractShape;
using cad::modeller::ScreenMode;
using cad::modeller::occt::OcctCanvas;

class wxOcctPanelStyle;

class wxOccPanel: public wxPanel, public AIS_ViewController, public OcctCanvas
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

        ~wxOccPanel() override;

        void SetStyle(const wxOcctPanelStyle &style);


        void ClearAll() final;
        void AddShape(Handle(AIS_InteractiveObject) shape) final;
        void RemoveShape(Handle(AIS_InteractiveObject) shape) final;
        bool ContainsShapes(const std::vector<Handle(AIS_InteractiveObject)> &objects) final;

        void ShowGrid(bool show = true);
        bool IsGridShown(void) const;
        void DeleteSelected(void);
        void Test(void);

        void SetScreenMode(ScreenMode mode);
        ScreenMode GetScreenMode(void) const;

        Handle(V3d_View) GetView(void)
        {
            return m_view;
        }

        Handle(AIS_ViewCube) GetViewCube(void)
        {
            return m_view_cube;
        }

    protected:
        ///
        void OnPaint(wxPaintEvent &event);
        void OnResize(wxSizeEvent &event);
        /// Mouse wheel event handler. Default behavior:
        /// zoom in / zoom out on mouse wheel rotating
        void OnMouseWheel(wxMouseEvent &event);
        void OnMouseMove(wxMouseEvent &event);
        void OnLeftMouseButtonDown(wxMouseEvent &event);
        void OnLeftMouseButtonUp(wxMouseEvent &event);
        void OnRightMouseButtonDown(wxMouseEvent &event);

    private:
        inline Aspect_VKeyMouse GetMouseButton(wxMouseEvent &event) const;
        inline Aspect_VKeyFlags GetPressedKey(void) const;
        inline void CreateViewCube(void);
        inline gp_Pnt GetIntersectionPoint(int mouse_x, int mouse_y);
        void MoveInterractor(wxMouseEvent &event);

        gp_Pln m_plane;
        Handle(AIS_Line) tmp_line;

        double m_scale_factor;
        bool m_mouse_lb_clicked;
        int m_last_x, m_last_y;

        TCollection_ExtendedString m_panel_name;
        Handle(Aspect_DisplayConnection) m_display_connection;
        Handle(OpenGl_GraphicDriver) m_graphic_driver;
        Handle_WNT_Window m_window;
        Handle(V3d_Viewer) m_viewer;
        Handle(V3d_View) m_view;
        Handle(AIS_InteractiveContext) m_context;
        Handle(AIS_ViewCube) m_view_cube;

        ObjectPool m_object_pool;
        Handle(AIS_Shape) aisthing;

        ScreenMode m_mode;

    DECLARE_EVENT_TABLE()
};

#endif // WXOCCPANEL_H
