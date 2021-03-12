#ifndef VIEWPANEL_H_INCLUDED
#define VIEWPANEL_H_INCLUDED

#include "wx/panel.h"
#include "screen.h"
#include "../builders/abstractbuilder.h"

class ViewPanel: public wxPanel
{
    public:
        ViewPanel(wxWindow *parent,
                    wxWindowID winid = wxID_ANY,
                    const wxPoint &pos = wxDefaultPosition,
                    const wxSize &size = wxDefaultSize,
                    long style = wxTAB_TRAVERSAL | wxNO_BORDER,
                    const wxString &name = wxPanelNameStr);

        virtual ~ViewPanel();


        // Sets screen size for drafting
        // After screen size changed the screen panel is to be refreshed to redraw all entities
        void SetScreenSize(double width, double height);

        void CancelCommand(void);

        void DeleteSelection(void);

        void CreateEntityByPoints(AbstractBuilder *builder);

        //
        //TODO
        //
        DrawManager* GetDrawManager(void)
        {
            return m_screen.GetDrawManager();
        }

    protected:
        // Event handlers
        void OnPaint(wxPaintEvent &event);
        void OnResize(wxSizeEvent &event);
        void OnMouseMove(wxMouseEvent &event);
        void OnMouseLeftButtonDown(wxMouseEvent &event);
        void OnMouseLeftButtonUp(wxMouseEvent &event);
        void OnMouseWheel(wxMouseEvent &event);
        void OnMouseWheelDown(wxMouseEvent &event);
        void OnMouseWheelUp(wxMouseEvent &event);

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

        Screen m_screen;

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

    wxDECLARE_EVENT_TABLE();
};

#endif // VIEWPANEL_H_INCLUDED
