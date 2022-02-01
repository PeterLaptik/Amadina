#include "point.h"
#include "../geometry/geometry.h"
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
    return geometry::calculate_distance(pt.x, pt.y, pt.z, x, y, z);
}

bool Point::IsNearPoint(const Point &pt, double region_radius)
{
    return region_radius>geometry::calculate_distance(pt.x, pt.y, pt.z, x, y, z);
}

bool Point::IsInSquare(const Point &top_left, const Point &bottom_right)
{
    return ((x>=top_left.x && x<=bottom_right.x)
       &&(y<=top_left.y && y>=bottom_right.y));
}

void Point::GetSnapPoints(std::vector<Point> &vec) const
{
    vec.push_back(*this);
}

void Point::MoveTo(double delta_x, double delta_y, double delta_z)
{
    x += delta_x;
    y += delta_y;
    z += delta_z;
}

Entity* Point::Clone(void) const
{
    return new Point(*this);
}
