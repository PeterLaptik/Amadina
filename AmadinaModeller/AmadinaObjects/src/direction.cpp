#include "direction.h"

cad::model::geom::Direction::Direction()
    : m_x(0.0), m_y(0.0), m_z(1.0)
{ }

cad::model::geom::Direction::Direction(double x, double y, double z)
    : m_x(x), m_y(y), m_z(z)
{ }

void cad::model::geom::Direction::SetAngles(double x, double y, double z)
{
    m_x = x;
    m_y = y;
    m_z = z;
}

void cad::model::geom::Direction::GetAngles(double *x, double *y, double *z) const
{
    *x = m_x;
    *y = m_y;
    *z = m_z;
}

double cad::model::geom::Direction::GetX() const
{
    return m_x;
}

double cad::model::geom::Direction::GetY() const
{
    return m_y;
}

double cad::model::geom::Direction::GetZ() const
{
    return m_z;
}