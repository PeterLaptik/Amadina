#include "circle.h"
#include "line.h"
#include <math.h>

Circle::Circle()
        : m_center(Point(0,0)), m_radius(1.0)
{ }

Circle::Circle(const Point &pt1, const double &radius)
        : m_center(pt1), m_radius(radius)
{ }

Circle::Circle(const double &x, const double &y, const double &radius)
        : m_center(Point(x, y)), m_radius(radius)
{ }

Circle::~Circle()
{ }


void Circle::Draw(IAdapterDC &dc)
{
    dc.CadDrawCircle(m_center, m_radius);
}

void Circle::DrawHighlighted(IAdapterDC &dc)
{
    dc.CadSetColour(Colour(255,0,0));
    dc.CadDrawCircle(m_center, m_radius);
}

const Point& Circle::GetCenterPoint(void) const
{
    return m_center;
}

double Circle::GetRadius(void) const
{
    return m_radius;
}

void Circle::GetSnapPoints(std::vector<Point> &vec) const
{
    double x = m_center.GetX();
    double y = m_center.GetY();
    vec.push_back(Point(x, y + m_radius));
    vec.push_back(Point(x, y - m_radius));
    vec.push_back(Point(x + m_radius, y));
    vec.push_back(Point(x - m_radius, y));
}

void Circle::GetCenterPoints(std::vector<Point> &vec) const
{
    vec.push_back(m_center);
}

void Circle::GetPrimitives(std::vector<Entity*> &vec)
{
    vec.push_back(this);
}

double Circle::DistanceFrom(const Point &pt) const
{
    double x0 = m_center.GetX();
    double y0 = m_center.GetY();
    double x = pt.GetX();
    double y = pt.GetY();
    double distance_from_center = sqrt(pow(x-x0,2) + pow(y-y0,2));
    return fabs(distance_from_center - m_radius);
}

void Circle::MoveTo(double delta_x, double delta_y, double delta_z)
{
    int x = m_center.GetX() + delta_x;
    int y = m_center.GetY() + delta_y;
    int z = m_center.GetZ() + delta_z;
    m_center.SetX(x);
    m_center.SetY(y);
    m_center.SetZ(z);
}

Entity* Circle::Clone()
{
    return new Circle(m_center, m_radius);
}
