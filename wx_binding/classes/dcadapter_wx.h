#ifndef DCADAPTER_WX_H_INCLUDED
#define DCADAPTER_WX_H_INCLUDED

#include <wx/dcbuffer.h>

// Kernel dependencies
#include "entities/point.h"

class wxAdapterDC: public wxBufferedPaintDC, public IAdapterDC
{
    public:
        wxAdapterDC(wxWindow *win, wxSize size);

        virtual ~wxAdapterDC();

        virtual void CadClear(void);

        virtual void CadDrawPoint(const Point &pt);

        virtual void CadDrawLine(const Point &pt1, const Point &pt2);

        virtual void CadDrawLine(double x1, double y1, double x2, double y2);

        virtual void CadDrawCircle(const Point &pt, const double &radius);

        virtual void CadDrawArc(const Point &pt_center, const Point &pt_start, const Point &pt_end);

        virtual void CadDrawConstraintLine(double x1, double y1, double x2, double y2);

        virtual void CadDrawConstraintSquare(double x1, double y1, double x2, double y2);

        virtual void CadSetColour(const Colour &colour);

        virtual void CadSetLayer(Layer *layer);

        // Overridden method of a base class
        // Includes additional scale calculation (length per pixel)
        virtual void SetBorders(double left, double right, double top, double bottom);

        virtual void GetBorders(double *left, double *right, double *top, double *bottom) const
        {
            *left = m_borders.left;
            *right = m_borders.right;
            *top = m_borders.top;
            *bottom = m_borders.bottom;
        }

        void GetScale(double *x, double *y) const;

        virtual const Colour& GetBackgroundColour(void) const;
        virtual void SetBackgroundColour(const Colour &colour);

        virtual void CadSetHighlited(bool is_highlited = true) override;

    protected:
        inline void TransformCoordinatesToView(double &x1, double &y1) const;
        inline void TransformCoordinatesToView(double &x1, double &y1, double &x2, double &y2) const;
        inline bool IsLineInsideScreen(const double& x1, const double& y1,
                     const double& x2, const double& y2) const;
        inline wxColour GetHighlightColour(void) const;
        inline unsigned int IncrementColourValue(unsigned int val, int step) const;

    private:
        int BORDER_MARGIN;
        bool m_is_highlited;

        struct Border
        {
            double left;
            double right;
            double top;
            double bottom;
        } m_borders;

        double x_scale;
        double y_scale;

        int m_width;
        int m_height;
        Colour m_colour;
        Colour m_background_colour;

        Layer *m_layer;

        struct DeviceColours
        {
            Colour background;
            Colour pen;
        } m_colours;
};

#endif // DCADAPTER_WX_H_INCLUDED
