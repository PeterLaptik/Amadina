#include "circle.h"
#include "line.h"
#include "../geometry/geometry.h"
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

bool Circle::IsNearPoint(const Point &pt, double region_radius)
{
    double rad = geometry::calculate_distance(pt.GetX(), pt.GetY(), pt.GetZ(),
                                        m_center.GetX(), m_center.GetY(), m_center.GetZ());
    return fabs(rad - m_radius) < region_radius;
}

double Circle::DistanceFrom(const Point &pt) const
{
    double x0 = m_center.GetX();
    double y0 = m_center.GetY();
    double x = pt.GetX();
    double y = pt.GetY();
    double distance_from_center = sqrt((x-x0)*(x-x0) + (y-y0)*(y-y0));
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
