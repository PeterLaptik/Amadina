#ifndef INTERSECTIONS_H_INCLUDED
#define INTERSECTIONS_H_INCLUDED

#include "../api/exports.h"
#include <vector>

class Entity;
class Point;
class Line;
class Circle;

namespace cad
{
    namespace geometry
    {
        // Functions for intersections calculations.
        // Each function receive two entities to compute intersections and vector of points to write intersections points.

        int DLL_EXPORT get_border_margin(void);

        // General case: two abstract entities
        void DLL_EXPORT calculate_intersections(Entity *entity_1, Entity *entity_2, std::vector<Point> &points);

        // Line-line intersection
        void DLL_EXPORT intersections(Line *line_1, Line *line_2, std::vector<Point> &points);

        // Circle-line intersection
        void DLL_EXPORT intersections(Line *line, Circle *circle, std::vector<Point> &points);

        // Circle-circle intersection
        void DLL_EXPORT intersections(Circle *circle_1, Circle *circle_2, std::vector<Point> &points);

        // Screen borders intersections calculations
        bool DLL_EXPORT border_intersection(double &x1, double &y1, double &x2, double &y2,
                                 const Point &top_left, const Point &bottom_right);

        bool line_line_intersection(const Line &line_1, const Line &line_2, Point& p);
    }
}

#endif // INTERSECTIONS_H_INCLUDED
