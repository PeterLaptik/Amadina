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

bool Line::IsNearPoint(const Point &pt, double region_radius)
{
    double x_max = std::max(m_pt1.GetX(), m_pt2.GetX());
    double x_min = std::min(m_pt1.GetX(), m_pt2.GetX());
    double y_max = std::max(m_pt1.GetY(), m_pt2.GetY());
    double y_min = std::min(m_pt1.GetY(), m_pt2.GetY());
    double z_max = std::max(m_pt1.GetZ(), m_pt2.GetZ());
    double z_min = std::min(m_pt1.GetZ(), m_pt2.GetZ());
    double x = pt.GetX();
    double y = pt.GetY();
    double z = pt.GetZ();
    if((x>x_max+region_radius)
       || (y>y_max+region_radius)
       || (z>z_max+region_radius)
       || (x<x_min-region_radius)
       || (y<y_min-region_radius)
       || (z<z_min-region_radius))
        return false;

    return DistanceFrom(pt)<region_radius;
}

bool Line::IsInSquare(const Point &top_left, const Point &bottom_right)
{
    return m_pt1.IsInSquare(top_left,bottom_right)
            && m_pt2.IsInSquare(top_left,bottom_right);
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
        double d1 = sqrt((x1-px)*(x1-px) + (y1-py)*(y1-py));
        double d2 = sqrt((x0-px)*(x0-px) + (y0-py)*(y0-py));
        distance = std::min(d1,d2);
    }
    return distance;
}

Entity* Line::Clone() const
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
