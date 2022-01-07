#ifndef DC_H_INCLUDED
#define DC_H_INCLUDED

class Point;
class Colour;
class Layer;

///\brief Device context interface for screen interface.
/// Contains methods to be implemented for screen implementations
/// and appears an adapter for GUI-dependent contexts
class IAdapterDC
{
    public:
        virtual void CadClear(void) = 0;

        virtual void CadDrawPoint(const Point &pt) = 0;

        virtual void CadDrawLine(const Point &pt1, const Point &pt2) = 0;

        virtual void CadDrawLine(double x1, double y1, double x2, double y2) = 0;

        virtual void CadDrawCircle(const Point &pt, const double &radius) = 0;

        virtual void CadDrawArc(const Point &pt_center, const Point &pt_start, const Point &pt_end) = 0;

        virtual void CadSetColour(const Colour &colour) = 0;


        virtual void CadDrawConstraintLine(double x1, double y1, double x2, double y2)
        {
            CadDrawLine(x1, y1, x2, y2);
        }

        virtual void CadSetLayer(Layer *layer) = 0;

        virtual void SetBorders(double left, double right, double top, double bottom) = 0;

        virtual void GetBorders(double *left, double *right, double *top, double *bottom) const = 0;

        virtual const Colour& GetBackgroundColour(void) const = 0;

        virtual void SetBackgroundColour(const Colour &colour) = 0;
};

#endif // DC_H_INCLUDED
