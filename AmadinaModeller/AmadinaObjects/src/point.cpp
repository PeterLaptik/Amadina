#include "point.h"
#include <limits>

cad::model::flat::Point::Point()
    : m_x(std::numeric_limits<double>::max()),
    m_y(std::numeric_limits<double>::max()),
    m_z(std::numeric_limits<double>::max())
{ }

cad::model::flat::Point::Point(double x, double y, double z)
    : m_x(x), m_y(y), m_z(z)
{ }

void cad::model::flat::Point::SetCoordinates(double x, double y, double z = 0.0)
{
    m_x = x;
    m_y = y;
    m_z = z;
}

void cad::model::flat::Point::SetX(double x)
{
    m_x = x;
}

void cad::model::flat::Point::SetY(double y)
{
    m_y = y;
}

void cad::model::flat::Point::SetZ(double z)
{
    m_z = z;
}

double cad::model::flat::Point::GetX() const
{
    return m_x;
}

double cad::model::flat::Point::GetY() const
{
    return m_y;
}

double cad::model::flat::Point::GetZ() const
{
    return m_z;
}

bool cad::model::flat::Point::IsSet() const
{
    return m_x != std::numeric_limits<double>::max();
}

void cad::model::flat::Point::AssignCanvas(AbstractCanvas *cnv)
{
    // empty implementation for 'AbstractCanvas'
}

void cad::model::flat::Point::DrawShape()
{
    // empty implementation for 'AbstractCanvas'
}

void cad::model::flat::Point::RemoveShape()
{
    // empty implementation for 'AbstractCanvas'
}