#ifndef DCADAPTER_WX_H_INCLUDED
#define DCADAPTER_WX_H_INCLUDED

#include <wx/dcbuffer.h>
#include "../entities/point.h"

class wxAdapterDC: public wxBufferedPaintDC, public IAdapterDC
{
    public:
        wxAdapterDC(wxWindow *win, wxSize size);

        virtual ~wxAdapterDC();

        virtual void CadDrawPoint(const Point &pt);

        virtual void CadDrawLine(const Point &pt1, const Point &pt2);

        virtual void CadDrawLine(double x1, double y1, double x2, double y2);

        virtual void CadDrawCircle(const Point &pt, const double &radius);

        virtual void CadDrawConstraintLine(double x1, double y1, double x2, double y2);

        virtual void CadSetColour(const Colour &colour);

        void SetBorders(double left, double right, double top, double bottom);
        void GetBorders(double *left, double *right, double *top, double *bottom) const;
        void GetScale(double *x, double *y) const;

    protected:

    private:
        inline void TransformCoordinatesToView(double &x1, double &y1);
        inline void TransformCoordinatesToView(double &x1, double &y1, double &x2, double &y2);

        int m_width;
        int m_height;
        Colour m_colour;

};

#endif // DCADAPTER_WX_H_INCLUDED
