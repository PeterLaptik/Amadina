#include "line.h"
#include <math.h>

Line::Line()
{ }

Line::Line(const Point &pt1, const Point &pt2)
        :m_pt1(pt1), m_pt2(pt2)
{ }

Line::Line(const double &x1, const double &y1, const double &x2, const double &y2)
{
    m_pt1.SetX(x1);
    m_pt1.SetY(y1);
    m_pt2.SetX(x2);
    m_pt2.SetY(y2);
}

Line::~Line()
{ }


void Line::CalculateLength()
{
    m_length = pow(pow(m_pt1.GetX()-m_pt2.GetX(),2)+pow(m_pt1.GetY()-m_pt2.GetY(),2), 0.5);
}

void Line::Draw(IAdapterDC &dc)
{
    dc.CadDrawLine(m_pt1, m_pt2);
}

void Line::GetSnapPoints(std::vector<std::pair<Entity*,Point>> &vec)
{
    vec.push_back(std::pair<Entity*,Point>(this, m_pt1));
    vec.push_back(std::pair<Entity*,Point>(this, m_pt2));
}

void Line::GetCenterPoints(std::vector<std::pair<Entity*, Point>> &vec)
{
    double x1 = m_pt1.GetX();
    double y1 = m_pt1.GetY();
    double x2 = m_pt2.GetX();
    double y2 = m_pt2.GetY();

    if(x1>x2)
        std::swap(x1, x2);

    if(y1>y2)
        std::swap(y1, y2);

    vec.push_back(std::pair<Entity*,Point>(this, Point(x1+(x2-x1)/2, y1+(y2-y1)/2)));
}
