#include "direction_vector.h"

using cad::model::geom::Direction;
using cad::model::flat::Point;

cad::model::geom::DirectionVector::DirectionVector(const Point &p, const Direction &dir)
    : m_center(p), m_direction(dir)
{ }

cad::model::geom::DirectionVector::DirectionVector(const Point &p)
    : m_center(p)
{ }

cad::model::geom::DirectionVector::DirectionVector()
    : m_center(0, 0, 0)
{
}

void cad::model::geom::DirectionVector::SetStartPoint(const Point &p)
{
    m_center = p;
}

void cad::model::geom::DirectionVector::SetDirection(const Direction &dir)
{
    m_direction = dir;
}

const Point &cad::model::geom::DirectionVector::GetStartPoint() const
{
    return m_center;
}

const Direction &cad::model::geom::DirectionVector::GetDirection() const
{
    return m_direction;
}