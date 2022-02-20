#ifndef ELLIPSE_H_INCLUDED
#define ELLIPSE_H_INCLUDED

#include "entity.h"
#include "point.h"

class Ellipse: public Entity
{
    public:
        Ellipse();
        Ellipse(const Point &pt1, const Point &pt2, const double &a);
        virtual ~Ellipse();

        virtual void Draw(IAdapterDC &dc) override;
        virtual void DrawHighlighted(IAdapterDC &dc) override;
        virtual bool IsNearPoint(const Point &pt, double region_radius) override;
        bool IsInSquare(const Point &top_left, const Point &bottom_right) override;
        virtual double DistanceFrom(const Point &pt) const override;
        virtual void GetSnapPoints(std::vector<Point> &vec) const override;
        virtual void GetCenterPoints(std::vector<Point> &vec) const override;
        virtual void MoveTo(double delta_x, double delta_y, double delta_z = 0.0) override;
        virtual Entity* Clone(void) const override;

        const Point& GetCenterPoint(void) const;
        double GetRadius(void) const;

    private:
        Point f1;
        Point f2;
        double a;
};

#endif // ELLIPSE_H_INCLUDED
