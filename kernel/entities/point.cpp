#include "point.h"
#include <math.h>

Point::Point()
    :x(0), y(0), z(0)
{ }

Point::Point(double x_coord, double y_coord, double z_coord):
        x(x_coord), y(y_coord), z(z_coord)
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
    double x1 = pt1.GetX();
    double y1 = pt1.GetY();
    double z1 = pt1.GetZ();

    double x2 = pt2.GetX();
    double y2 = pt2.GetY();
    double z2 = pt2.GetZ();

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
