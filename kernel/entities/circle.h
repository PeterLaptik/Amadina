#ifndef CIRCLE_H_INCLUDED
#define CIRCLE_H_INCLUDED

#include "point.h"

class Circle: public Entity
{
    public:
        Circle(const Point &pt1, const double &radius);
        Circle(const double &x, const double &y, const double &radius);
        virtual ~Circle();

        virtual void Draw(IAdapterDC &dc);

        Point GetCenterPoint(void) const;

        double GetRadius(void) const;

        virtual void GetSnapPoints(std::vector<Point> &vec) const;

        virtual void GetCenterPoints(std::vector<Point> &vec) const;

        virtual void IntersectsWith(Entity* entity, std::vector<Point> &points) const;

    protected:

    private:
        Circle();

        Point m_center;
        double m_radius;
};

#endif // CIRCLE_H_INCLUDED
