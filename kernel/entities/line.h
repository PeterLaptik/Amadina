#ifndef LINE_H_INCLUDED
#define LINE_H_INCLUDED

#include "entity.h"
#include "point.h"

// Forward declaration for intersections calculations
class Circle;


class Line: public Entity
{
    public:
        Line(const Point &pt1, const Point &pt2);
        Line(const double &x1, const double &y1, const double &x2, const double &y2);
        virtual ~Line();

        virtual void Draw(IAdapterDC &dc);

        virtual void GetSnapPoints(std::vector<Point> &vec) const;

        virtual void GetCenterPoints(std::vector<Point> &vec) const;

        virtual void IntersectsWith(Entity* entity, std::vector<Point> &points) const;

    protected:

    private:
        Line();
        void CalculateLength(void);
        void LineIntersection(Line *line, std::vector<Point> &points) const;
        void CircleIntersection(Circle *circle, std::vector<Point> &points) const;

        Point m_pt1;
        Point m_pt2;
        double m_length;
};

#endif // LINE_H_INCLUDED
