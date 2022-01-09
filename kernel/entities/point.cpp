#include "point.h"
#include <math.h>

Point::Point()
    :x(0), y(0), z(0)
{ }

Point::Point(double x_coord, double y_coord, double z_coord):
        x(round(x_coord*1000)/1000),
        y(round(y_coord*1000)/1000),
        z(round(z_coord*1000)/1000)
{ }

Point::~Point()
{ }

bool Point::operator==(const Point &pt)
{
    return (pt.x==x)&&(pt.x==y)&&(pt.x==z);
}

void Point::Draw(IAdapterDC &dc)
{
    dc.CadDrawPoint(*this);
}

void Point::DrawHighlighted(IAdapterDC &dc)
{
    dc.CadSetColour(Colour(255,0,0));
    dc.CadDrawPoint(*this);
}

double Point::DistanceFrom(const Point &pt) const
{
    return Point::GetDistanceBetween(*this, pt);
}

double Point::GetDistanceBetween(const Point &pt1, const Point &pt2)
{
    double x1 = pt1.x;
    double y1 = pt1.y;
    double z1 = pt1.z;

    double x2 = pt2.x;
    double y2 = pt2.y;
    double z2 = pt2.z;

    return sqrt(pow(fabs(x1 - x2), 2) + pow(fabs(y1 - y2), 2) + pow(fabs(z1 - z2), 2));
}

void Point::GetSnapPoints(std::vector<Point> &vec) const
{
    vec.push_back(*this);
}

Entity* Point::Clone(void)
{
    return new Point(*this);
}
