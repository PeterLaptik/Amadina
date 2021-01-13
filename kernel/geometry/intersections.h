#ifndef INTERSECTIONS_H_INCLUDED
#define INTERSECTIONS_H_INCLUDED

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

        // General case: two abstract entities
        void calculate_intersections(Entity *entity_1, Entity *entity_2, std::vector<Point> &points);

        // Line-line intersection
        void intersections(Line *line_1, Line *line_2, std::vector<Point> &points);

        // Circle-line intersection
        void intersections(Line *line, Circle *circle, std::vector<Point> &points);

        // Circle-circle intersection
        void intersections(Circle *circle_1, Circle *circle_2, std::vector<Point> &points);
    }
}

#endif // INTERSECTIONS_H_INCLUDED
