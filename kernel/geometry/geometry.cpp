#include "geometry.h"
#include "math.h"

static const double PI = 3.14;

///\brief Calculates angle of point (x,y) in coordinates system centered in point (x0,y0)
/// Following scheme shows angles values on a flat surface:
/// 
///                     90 deg.
///                       |
///                       |
///   180 deg. --------(x0,y0)--------- 0 deg.
///                       |
///                       |
///                     270 deg.
/// 
///\param x0 - coordinate system ceneter's x
///\param y0 - coordinate system ceneter's y
///\param x - point's x
///\param y - point's y
///\return angle value in degrees, always positive. See scheme above
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

///\brief Calculates distance between two points with coordinates [x1,y1] and [x2,y2]
///\param x1, y1 - first point coordinates
///\param x2, y2 - second point coordinate
double geometry::calculate_distance(double x1, double y1, double x2, double y2)
{
    return sqrt((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2));
}
