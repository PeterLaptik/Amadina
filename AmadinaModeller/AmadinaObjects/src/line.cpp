#include "line.h"

using cad::model::flat::Point;

cad::model::flat::Line::Line(const Point &p1, const Point &p2)
    : m_first(p1), m_second(p2)
{ }


void  cad::model::flat::Line::SetPoints(const Point &p1, const Point &p2)
{
    m_first = p1;
    m_second = p2;
}

void  cad::model::flat::Line::SetFirstPoint(const Point &p)
{
    m_first = p;
}

void  cad::model::flat::Line::SetSecondPoint(const Point &p)
{
    m_second = p;
}

const Point &cad::model::flat::Line::GetFirstPoint() const
{
    return m_first;
}

const Point &cad::model::flat::Line::GetSecondPoint() const
{
    return m_second;
}
