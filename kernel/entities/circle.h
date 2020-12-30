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

        virtual void GetSnapPoints(std::vector<std::pair<Entity*,Point>> &vec);

        virtual void GetCenterPoints(std::vector<std::pair<Entity*, Point>> &vec);

    protected:

    private:
        Circle();

        Point m_center;
        double m_radius;
};

#endif // CIRCLE_H_INCLUDED
