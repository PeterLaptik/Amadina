#include "point.h"

cad::modeller::shapes2D::Point::Point(double x, double y, double z)
	: m_x(x), m_y(y), m_z(z)
{ }

void cad::modeller::shapes2D::Point::SetCoordinates(double x, double y, double z = 0.0)
{
	m_x = x;
	m_y = y;
	m_z = z;
}

void cad::modeller::shapes2D::Point::SetX(double x)
{
	m_x = x;
}

void cad::modeller::shapes2D::Point::SetY(double y)
{
	m_y = y;
}

void cad::modeller::shapes2D::Point::SetZ(double z)
{
	m_z = z;
}

double cad::modeller::shapes2D::Point::GetX() const
{
	return m_x;
}

double cad::modeller::shapes2D::Point::GetY() const
{
	return m_y;
}

double cad::modeller::shapes2D::Point::GetZ() const
{
	return m_z;
}

void cad::modeller::shapes2D::Point::Draw(AbstractCanvas &cnv)
{
	// no concrete canvas defined
}