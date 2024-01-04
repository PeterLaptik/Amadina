#include "direction_vector.h"

using cad::modeller::geometry::Direction;
using cad::modeller::shapes2D::Point;

cad::modeller::geometry::DirectionVector::DirectionVector(const Point &p, const Direction &dir)
    : m_center(p), m_direction(dir)
{ }

cad::modeller::geometry::DirectionVector::DirectionVector(const Point &p)
    : m_center(p)
{ }

cad::modeller::geometry::DirectionVector::DirectionVector()
    : m_center(0, 0, 0)
{ }

void cad::modeller::geometry::DirectionVector::SetStartPoint(const Point & p)
{
    m_center = p;
}

void cad::modeller::geometry::DirectionVector::SetDirection(const Direction & dir)
{
    m_direction = dir;
}

const Point& cad::modeller::geometry::DirectionVector::GetStartPoint() const
{
    return m_center;
}

const Direction& cad::modeller::geometry::DirectionVector::GetDirection() const
{
    return m_direction;
}