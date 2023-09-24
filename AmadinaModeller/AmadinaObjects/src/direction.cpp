#include "direction.h"

cad::modeller::geometry::Direction::Direction()
	: m_x(0.0), m_y(0.0), m_z(1.0)
{ }

cad::modeller::geometry::Direction::Direction(double x, double y, double z)
	: m_x(x), m_y(y), m_z(z)
{ }

void cad::modeller::geometry::Direction::SetAngles(double x, double y, double z)
{
	m_x = x;
	m_y = y;
	m_z = z;
}

double cad::modeller::geometry::Direction::GetX() const
{
	return m_x;
}

double cad::modeller::geometry::Direction::GetY() const
{
	return m_y;
}

double cad::modeller::geometry::Direction::GetZ() const
{
	return m_z;
}