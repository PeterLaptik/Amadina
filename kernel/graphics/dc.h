#ifndef DC_H_INCLUDED
#define DC_H_INCLUDED

#include "colour.h"

class Point;

// Abstract device context for plotting
// Any implementation for a concrete widget type has to implement this interface
class IAdapterDC
{
    public:

        virtual void CadDrawPoint(const Point &pt) = 0;

        virtual void CadDrawLine(const Point &pt1, const Point &pt2) = 0;

        virtual void CadDrawLine(double x1, double y1, double x2, double y2) = 0;

        virtual void CadDrawCircle(const Point &pt, const double &radius) = 0;

        virtual void CadSetColour(const Colour &colour) = 0;

        virtual void CadDrawConstraintLine(double x1, double y1, double x2, double y2)
        {
            CadDrawLine(x1, y1, x2, y2);
        }

        virtual void SetBorders(double left, double right, double top, double bottom)
        {
            m_borders.left = left;
            m_borders.right = right;
            m_borders.top = top;
            m_borders.bottom = bottom;
        }

        virtual void GetBorders(double *left, double *right, double *top, double *bottom) const
        {
            *left = m_borders.left;
            *right = m_borders.right;
            *top = m_borders.top;
            *bottom = m_borders.bottom;
        }

    protected:
        // The fields have to be initialized in derived classes
        struct Border
        {
            double left;
            double right;
            double top;
            double bottom;
        } m_borders;

        double x_scale;
        double y_scale;

    private:

};

#endif // DC_H_INCLUDED
