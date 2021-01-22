#ifndef DC_H_INCLUDED
#define DC_H_INCLUDED

class Point;
class Colour;

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

        virtual void SetBorders(double left, double right, double top, double bottom) = 0;

        virtual void GetBorders(double *left, double *right, double *top, double *bottom) const = 0;

        virtual const Colour& GetBackgroundColour(void) const = 0;

        virtual void SetBackgroundColour(Colour colour) = 0;

    protected:


    private:


};

#endif // DC_H_INCLUDED
