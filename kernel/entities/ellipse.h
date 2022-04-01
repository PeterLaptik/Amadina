#ifndef ELLIPSE_H_INCLUDED
#define ELLIPSE_H_INCLUDED

#include "entity.h"
#include "point.h"

class Ellipse: public Entity
{
    public:
        Ellipse();
        Ellipse(const Point &pt1, const Point &pt2, const double &ra, const double &rb);
        virtual ~Ellipse();

        virtual void Draw(IAdapterDC &dc) override;
        virtual bool IsNearPoint(const Point &pt, double region_radius) override;
        bool IsInSquare(const Point &top_left, const Point &bottom_right) override;
        virtual double DistanceFrom(const Point &pt) const override;
        virtual void GetSnapPoints(std::vector<Point> &vec) const override;
        virtual void GetCenterPoints(std::vector<Point> &vec) const override;
        virtual void MoveTo(double delta_x, double delta_y, double delta_z = 0.0) override;
        virtual Entity* Clone(void) const override;

        void SetFocuses(const Point &focus_1, const Point &focus_2);
        void SetCenter(const double &x, const double &y, const double &z = 0);
        void SetSemiAxisLong(double axis_a);
        void SetSemiAxisShort(double axis_b);

        void GetFocuses(Point &focus_1, Point &focus_2) const;
        void GetCenter(double &x, double &y, double &z);
        double GetSemiAxisLong(void) const;
        double GetSemiAxisShort(void) const;

    private:
        Point f1;
        Point f2;
        Point center;
        double a;
        double b;
};

#endif // ELLIPSE_H_INCLUDED
