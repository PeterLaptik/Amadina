#include "line.h"
#include "circle.h"
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

void Line::GetSnapPoints(std::vector<Point> &vec) const
{
    vec.push_back(m_pt1);
    vec.push_back(m_pt2);
}

void Line::GetCenterPoints(std::vector<Point> &vec) const
{
    double x1 = m_pt1.GetX();
    double y1 = m_pt1.GetY();
    double x2 = m_pt2.GetX();
    double y2 = m_pt2.GetY();

    if(x1>x2)
        std::swap(x1, x2);

    if(y1>y2)
        std::swap(y1, y2);

    vec.push_back(Point(x1+(x2-x1)/2, y1+(y2-y1)/2));
}

void Line::IntersectsWith(Entity* entity, std::vector<Point> &points) const
{
    Line *line = dynamic_cast<Line*>(entity);
    Circle *circle = dynamic_cast<Circle*>(entity);

    if(line)
        LineIntersection(line, points);

    if(circle)
        CircleIntersection(points);
}

void Line::LineIntersection(Line *line, std::vector<Point> &points) const
{
    double x1, x2, y1, y2;
    // First line
    x1 = m_pt1.GetX();
    y1 = m_pt1.GetY();
    x2 = m_pt2.GetX();
    y2 = m_pt2.GetY();

//    if(x1>x2)
//        std::swap(x1,x2);
//
//    if(y1>y2)
//        std::swap(x1,x2);

    // y1 = ax + c
    // y2 = bx + d
    double a = (y2 - y1)/(x2 - x1);
    double c = y1 + a*x1;

    // (x-x1)/(x2-x1)=(y-y1)/(y2-y1)
    // (x-x1)*((y2-y1)/(x2-x1))=(y-y1)
    // (x-x1)*a=(y-y1)
    //  a*x1 = y - y1
    //  y1 + a*x1 = y

    // Second line
    x1 = line->m_pt1.GetX();
    y1 = line->m_pt1.GetY();
    x2 = line->m_pt2.GetX();
    y2 = line->m_pt2.GetY();
    double b = (y2 - y1)/(x2 - x1);
    double d = y1 + a*x1;

    double x = (d - c)/(a - b);
    double y = a*(d - c)/(a - b) + c;
    points.push_back(Point(x,y));
}

void Line::CircleIntersection(std::vector<Point> &points) const
{

}
