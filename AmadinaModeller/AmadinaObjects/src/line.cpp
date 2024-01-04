#include "line.h"

using cad::modeller::shapes2D::Point;

cad::modeller::shapes2D::Line::Line(const Point &p1, const Point &p2)
	: m_first(p1), m_second(p2)
{ }


void  cad::modeller::shapes2D::Line::SetPoints(const Point &p1, const Point &p2)
{
	m_first = p1;
	m_second = p2;
}

void  cad::modeller::shapes2D::Line::SetFirstPoint(const Point &p)
{
	m_first = p;
}

void  cad::modeller::shapes2D::Line::SetSecondPoint(const Point &p)
{
	m_second = p;
}

const Point& cad::modeller::shapes2D::Line::GetFirstPoint() const
{
	return m_first;
}

const Point& cad::modeller::shapes2D::Line::GetSecondPoint() const
{
	return m_second;
}
