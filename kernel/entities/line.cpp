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
        CircleIntersection(circle, points);
}

void Line::LineIntersection(Line *line, std::vector<Point> &points) const
{
    double x1, x2, y1, y2;
    double x3, x4, y3, y4;

    // First line
    x1 = this->m_pt1.GetX();
    y1 = this->m_pt1.GetY();
    x2 = this->m_pt2.GetX();
    y2 = this->m_pt2.GetY();
    if(x1>x2)
    {
        std::swap(x1,x2);
        std::swap(y1,y2);
    }

    // Second line
    x3 = line->m_pt1.GetX();
    y3 = line->m_pt1.GetY();
    x4 = line->m_pt2.GetX();
    y4 = line->m_pt2.GetY();
    if(x3>x4)
    {
        std::swap(x3,x4);
        std::swap(y3,y4);
    }

    double t_denominator = (x1 - x2)*(y3 - y4) - (y1 - y2)*(x3 - x4);
    //double u_denominator = (x1 - x2)*(y3 - y4) - (y1 - y2)*(x3 - x4);
    if((t_denominator==0)/*||(u_denominator==0)*/)
        return;

    double t = ((x1 - x3)*(y3 - y4) - (y1 - y3)*(x3 - x4))/t_denominator;
    //double u = ((x1 - x2)*(y1 - y3) - (y1 - y2)*(x1 - x3))/u_denominator;
    double x = x1 + t*(x2 - x1);
    double y = y1 + t*(y2 - y1);

    if((x>x1)&&(x<x2)&&(x>x3)&&(x<x4))
        points.push_back(Point(x,y));
}

void Line::CircleIntersection(Circle *circle, std::vector<Point> &points) const
{
    double x1 = this->m_pt1.GetX();
    double y1 = this->m_pt1.GetY();
    double x2 = this->m_pt2.GetX();
    double y2 = this->m_pt2.GetY();
    if(x1>x2)
    {
        std::swap(x1,x2);
        std::swap(y1,y2);
    }

    double x0 = circle->GetCenterPoint().GetX();
    double y0 = circle->GetCenterPoint().GetY();
    double r = circle->GetRadius();

    double A = y2 - y1;
    double B = x1 - x2;
    double C = x2*y1 - x1*y2;

    double a = pow(A,2) + pow(B,2);
    double b = 2*A*C + 2*A*B*y0 - 2*pow(B,2)*x0;
    double c = pow(C,2) + 2*B*C*y0 - pow(B,2)*(pow(r,2) - pow(x0,2) - pow(y0,2));

    double sq_val = pow(b,2) - 4*a*c;
    if(sq_val<0)
        return;

    double x = (-b + pow(sq_val,0.5))/(2*a);
    double y = -(A*x + C)/B;
    if((x<x2)&&(x>x1))
        points.push_back(Point(x, y));

    x = (-b - pow(sq_val,0.5))/(2*a);
    y = -(A*x + C)/B;
    if((x<x2)&&(x>x1))
        points.push_back(Point(x, y));
}
