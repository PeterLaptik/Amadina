#ifndef VIEWPANEL_H_INCLUDED
#define VIEWPANEL_H_INCLUDED

#include "wx/panel.h"
#include "adapter.h"
#include "../entities/point.h"
#include "../processor/drawmanager.h"
#include "../builders/abstractbuilder.h"

class ViewPanel: public wxPanel, private Adapter
{
    public:
        ViewPanel(wxWindow *parent,
                    wxWindowID winid = wxID_ANY,
                    const wxPoint &pos = wxDefaultPosition,
                    const wxSize &size = wxDefaultSize,
                    long style = wxTAB_TRAVERSAL | wxNO_BORDER,
                    const wxString &name = wxPanelNameStr);

        virtual ~ViewPanel();


        void SetBorders(double left, double right, double top, double bottom);
        //
        // Positioning and scaling
        //
        // Sets real coordinates for the center of a panel
        // The panel is positioned using center point and width/height values
        void SetCenterPosition(Point point);
        void SetCenterPosition(double x, double y);
        // Returns center point (coordinates) of the panel
        Point GetCenterPosition(void) const;

        // Sets screen size for drafting
        // After screen size changed the screen panel is to be refreshed to redraw all entities
        void SetScreenSize(double width, double height);

        void CancelCommand(void);

        void DeleteSelection(void);

        void CreateEntityByPoints(AbstractBuilder *builder);

        DrawManager* GetDrawManager(void)
        {
            return &draw_manager;
        }

    protected:
        void OnPaint(wxPaintEvent &event);
        void OnResize(wxSizeEvent &event);
        void OnMouseMove(wxMouseEvent &event);
        void OnMouseLeftButtonDown(wxMouseEvent &event);
        void OnMouseLeftButtonUp(wxMouseEvent &event);
        void OnMouseWheel(wxMouseEvent &event);
        void OnMouseWheelDown(wxMouseEvent &event);
        void OnMouseWheelUp(wxMouseEvent &event);

        void PointPicked(double x, double y);

        enum State
        {
            STATE_NOTHING,
            STATE_PICKING_POINTS
        } canvas_state;
        AbstractBuilder *shape_builder;

        int width_px;
        int height_px;

        bool wheel_pressed;

        double snap_radius;

        Point m_center_coordinate;
        double m_draft_width;
        double m_draft_height;


    private:
        void AddTestShapes(void);
        void TransformCoordinatesToGlobal(double &x, double &y);
        void CalculateBestSnapRadius(void);
//        void TransformCoordinatesFromGlobal(double &x, double &y);

        // Screen position
        struct Borders
        {
            double left;
            double right;
            double top;
            double bottom;
        } borders;

        struct MouseCoordinates
        {
            double x;
            double y;
        } coordinates;

        int last_mouse_pos;
        DrawManager draw_manager;


    wxDECLARE_EVENT_TABLE();
};

#endif // VIEWPANEL_H_INCLUDED
