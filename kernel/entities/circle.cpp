#include "circle.h"

Circle::Circle()
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

void Circle::GetSnapPoints(std::vector<std::pair<Entity*,Point>> &vec)
{
    double x = m_center.GetX();
    double y = m_center.GetY();
    vec.push_back(std::pair<Entity*,Point>(this, Point(x, y + m_radius)));
    vec.push_back(std::pair<Entity*,Point>(this, Point(x, y - m_radius)));
    vec.push_back(std::pair<Entity*,Point>(this, Point(x + m_radius, y)));
    vec.push_back(std::pair<Entity*,Point>(this, Point(x - m_radius, y)));
}

void Circle::GetCenterPoints(std::vector<std::pair<Entity*, Point>> &vec)
{
    vec.push_back(std::pair<Entity*,Point>(this, m_center));
}
