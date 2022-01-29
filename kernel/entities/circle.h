#ifndef CIRCLE_H_INCLUDED
#define CIRCLE_H_INCLUDED

#include "point.h"

class Circle: public Entity
{
    public:
        Circle();
        Circle(const Point &pt1, const double &radius);
        Circle(const double &x, const double &y, const double &radius);
        virtual ~Circle();

        virtual void Draw(IAdapterDC &dc);

        virtual void DrawHighlighted(IAdapterDC &dc);

        const Point& GetCenterPoint(void) const;

        double GetRadius(void) const;

        virtual bool IsNearPoint(const Point &pt, double region_radius);

        virtual double DistanceFrom(const Point &pt) const;

        virtual void GetSnapPoints(std::vector<Point> &vec) const;

        virtual void GetCenterPoints(std::vector<Point> &vec) const;

        virtual void GetPrimitives(std::vector<Entity*> &vec);

        virtual void MoveTo(double delta_x, double delta_y, double delta_z = 0.0);

        virtual Entity* Clone(void);

    protected:

    private:
        Point m_center;
        double m_radius;
};

#endif // CIRCLE_H_INCLUDED
