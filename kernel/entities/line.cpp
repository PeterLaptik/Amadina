#include "line.h"
#include "circle.h"
#include <math.h>

Line::Line()
        :m_pt1(Point(0,0)), m_pt2(Point(0,1))
{ }

Line::Line(const Point &pt1, const Point &pt2)
        :m_pt1(pt1), m_pt2(pt2)
{
    CalculateLength();
}

Line::Line(const double &x1, const double &y1, const double &x2, const double &y2)
{
    m_pt1.SetX(x1);
    m_pt1.SetY(y1);
    m_pt2.SetX(x2);
    m_pt2.SetY(y2);
    CalculateLength();
}

Line::~Line()
{ }


void Line::CalculateLength()
{
    m_length = pow(pow(m_pt1.GetX()-m_pt2.GetX(),2)+pow(m_pt1.GetY()-m_pt2.GetY(),2), 0.5);
}

void Line::Draw(IAdapterDC &dc)
{
    dc.CadSetLayer(m_layer);
    dc.CadDrawLine(m_pt1, m_pt2);
}

void Line::DrawHighlighted(IAdapterDC &dc)
{
    Point pt1 = m_pt1;
    Point pt2 = m_pt2;
    //pt2.SetX(pt2.GetX()-1);
    //pt2.SetY(pt2.GetY()-1);
    dc.CadSetColour(Colour(255,0,0));
    dc.CadDrawLine(pt1, pt2);
}

double Line::DistanceFrom(const Point &pt) const
{
    double px = pt.GetX();
    double py = pt.GetY();
    double x0 = m_pt1.GetX();
    double x1 = m_pt2.GetX();
    double y0 = m_pt1.GetY();
    double y1 = m_pt2.GetY();

    double dx = x1 - x0;
    double dy = y1 - y0;

    double t = -((x0 - px)*(x1 - x0) + (y0 - py)*(y1 - y0))/(dx*dx + dy*dy);

    double distance = std::numeric_limits<double>::max();
    if((t>=0)&&(t<=1))
    {
        distance = fabs((dx*(y0 - py) - dy*(x0 - px)))/sqrt(dx*dx + dy*dy);
    }
    else
    {
        double d1 = sqrt(pow(x1-px,2) + pow(y1-py,2));
        double d2 = sqrt(pow(x0-px,2) + pow(y0-py,2));
        distance = std::min(d1,d2);
    }
    return distance;
}

Entity* Line::Clone()
{
    return new Line(m_pt1, m_pt2);
}

void Line::MoveTo(double delta_x, double delta_y, double delta_z)
{
    int x_1 = m_pt1.GetX() + delta_x;
    int y_1 = m_pt1.GetY() + delta_y;
    int z_1 = m_pt1.GetZ() + delta_z;
    int x_2 = m_pt2.GetX() + delta_x;
    int y_2 = m_pt2.GetY() + delta_y;
    int z_2 = m_pt2.GetZ() + delta_z;
    m_pt1 = Point(x_1, y_1, z_1);
    m_pt2 = Point(x_2, y_2, z_2);
}

void Line::SetStartPoint(const Point &pt)
{
    m_pt1 = pt;
    CalculateLength();
}

void Line::SetEndPoint(const Point &pt)
{
    m_pt2 = pt;
    CalculateLength();
}

const Point& Line::GetStartPoint(void) const
{
    return m_pt1;
}

const Point& Line::GetEndPoint(void) const
{
    return m_pt2;
}

double Line::GetLength() const
{
    return m_length;
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

void Line::GetPrimitives(std::vector<Entity*> &vec)
{
    vec.push_back(this);
}
