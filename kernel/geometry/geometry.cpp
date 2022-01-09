#include "geometry.h"
#include "math.h"

static const double PI = 3.14;

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

double geometry::calculate_distance(double x1, double y1, double x2, double y2)
{
    return sqrt((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2));
}
