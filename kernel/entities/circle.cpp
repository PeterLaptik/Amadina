#include "circle.h"
#include "line.h"

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

const Point& Circle::GetCenterPoint(void) const
{
    return m_center;
}

double Circle::GetRadius(void) const
{
    return m_radius;
}
