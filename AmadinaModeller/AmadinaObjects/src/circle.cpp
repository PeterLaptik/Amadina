#include "circle.h"

using cad::model::flat::Point;
using cad::model::geom::Direction;

cad::model::flat::Circle::Circle(const Point &p, double radius)
    : m_center(p), m_radius(radius)
{ }

cad::model::flat::Circle::Circle(double x, double y, double z, double radius)
    : m_center(x, y, z), m_radius(radius)
{ }

void cad::model::flat::Circle::SetCenter(const Point &p)
{
    m_center = p;
}

void cad::model::flat::Circle::SetRadius(double rad)
{
    m_radius = rad;
}

void cad::model::flat::Circle::SetDirection(const Direction &dir)
{
    m_direction = dir;
}

const Direction &cad::model::flat::Circle::GetDirection()const
{
    return m_direction;
}

const Point &cad::model::flat::Circle::GetCenter() const
{
    return m_center;
}

double cad::model::flat::Circle::GetRadius() const
{
    return m_radius;
}