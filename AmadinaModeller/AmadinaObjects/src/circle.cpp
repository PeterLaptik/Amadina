#include "circle.h"

using cad::modeller::shapes2D::Point;
using cad::modeller::geometry::Direction;

cad::modeller::shapes2D::Circle::Circle(const Point &p, double radius)
	: m_center(p), m_radius(radius)
{ }

cad::modeller::shapes2D::Circle::Circle(double x, double y, double z, double radius)
	: m_center(x, y, z), m_radius(radius)
{ }

void cad::modeller::shapes2D::Circle::SetCenter(const Point & p)
{
	m_center = p;
}

void cad::modeller::shapes2D::Circle::SetRadius(double rad)
{
	m_radius = rad;
}

void cad::modeller::shapes2D::Circle::SetDirection(const Direction & dir)
{
	m_direction = dir;
}

const Direction& cad::modeller::shapes2D::Circle::GetDirection()const
{
	return m_direction;
}

const Point& cad::modeller::shapes2D::Circle::GetCenter() const
{
	return m_center;
}

double cad::modeller::shapes2D::Circle::GetRadius() const
{
	return m_radius;
}