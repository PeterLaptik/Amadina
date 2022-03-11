#include "geometry.h"
#include <math.h>
#include <utility>

static const double PI = 3.14;

// Calculates angle of point (x,y) in coordinates system centered in point (x0,y0)
// Following scheme shows angles values on a flat surface:
//
//                     90 deg.
//                       |
//                       |
//   180 deg. --------(x0,y0)--------- 0 deg.
//                       |
//                       |
//                     270 deg.
//
// x0 - coordinate system ceneter's x
// y0 - coordinate system ceneter's y
// x - point's x
// y - point's y
// returns angle value in degrees, always positive. See scheme above
double geometry::calculate_angle(double x0, double y0, double x, double y)
{
    double length = sqrt((x0 - x) * (x0 - x) + (y0 - y) * (y0 - y));
    double sinus = fabs(y0 - y) / length;
    double row_angle = asin(sinus) * 180 / PI;

    // Quadrants
    double angle = 0;
    if (x >= x0 && y >= y0)
        angle = row_angle;
    else if (x >= x0 && y <= y0)
        angle = 360 - row_angle;
    else if (x <= x0 && y <= y0)
        angle = 180 + row_angle;
    else if (x <= x0 && y >= y0)
        angle = 180 - row_angle;

    return angle;
}

// Calculates angle of point (x,y) in coordinates system centered in point (x0,y0)
// Returns result in radians
double geometry::calculate_angle_rad(double x0, double y0, double x, double y)
{
    double length = sqrt((x0 - x) * (x0 - x) + (y0 - y) * (y0 - y));
    double sinus = fabs(y0 - y) / length;
    return asin(sinus);
}

// Calculates distance between two points with coordinates [x1,y1] and [x2,y2]
// x1, y1 - first point coordinates
// x2, y2 - second point coordinate
double geometry::calculate_distance(double x1, double y1, double x2, double y2)
{
    return sqrt((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2));
}

// Calculates distance between two points with coordinates [x1,y1,z1] and [x2,y2,z2]
// x1, y1, z1 - first point coordinates
// x2, y2, z2 - second point coordinate
double geometry::calculate_distance(double x1, double y1, double z1,
                           double x2, double y2, double z2)
{
    return sqrt((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2) + (z1-z2)*(z1-z2));
}

// Calculates center point on the line
// x1, y1 - first line point coordinates
// x2, y2 - second line point coordinates
// xc, yc - center point coordinates values (result)
void geometry::calculate_center_point(double x1, double y1, double x2, double y2,
                                double &xc, double &yc)
{
    if(x1>x2)
        std::swap(x1,x2);
    if(y1>y2)
        std::swap(y1,y2);

    xc = x1 + (x2 - x1)/2;
    yc = y1 + (y2 - y1)/2;
}

// Rotates point around center point.
// x, y - point coordinates
// angle - rotate angle value in radians
// xc, yc - center point ([x,y] is rotated around [xc,yc])
void geometry::rotate_point(double &x, double &y, const double &angle,
                                 const double &xc, const double &yc)
{
    // Shift to x-0-y point
    double x_tr = x - xc;
    double y_tr = y - yc;
    // Rotated values
    double rot_x = x_tr*cos(angle) - y_tr*sin(angle);
    double rot_y = x_tr*sin(angle) - y_tr*cos(angle);

//    double rot_x = x_tr*sin(angle) - y_tr*cos(angle);
//    double rot_y = x_tr*cos(angle) - y_tr*sin(angle);

    // Shift rollback
    x = xc + rot_x;
    y = yc + rot_y;
}
