#include "ellipse.h"

Ellipse::Ellipse()
{ }

Ellipse::Ellipse(const Point &pt1, const Point &pt2, const double &ra, const double &rb)
    : f1(pt1), f2(pt2), a(ra), b(rb)
{ }

Ellipse::~Ellipse()
{ }

void Ellipse::Draw(IAdapterDC &dc)
{
    dc.CadDrawEllipse(f1.GetX(), f1.GetY(), f2.GetX(), f2.GetY(), a, b);
}

bool Ellipse::IsNearPoint(const Point &pt, double region_radius)
{
    return false;
}

bool Ellipse::IsInSquare(const Point &top_left, const Point &bottom_right)
{
    return true;
}

double Ellipse::DistanceFrom(const Point &pt) const
{
    return std::numeric_limits<double>::max();
}

void Ellipse::GetSnapPoints(std::vector<Point> &vec) const
{

}

void Ellipse::GetCenterPoints(std::vector<Point> &vec) const
{

}

void Ellipse::MoveTo(double delta_x, double delta_y, double delta_z)
{

}

Entity* Ellipse::Clone() const
{
    Ellipse *clone = new Ellipse();
    clone->SetFocuses(f1, f2);
    clone->SetSemiAxisLong(a);
    clone->SetSemiAxisShort(b);
    return clone;
}

void Ellipse::SetFocuses(const Point &focus_1, const Point &focus_2)
{
    f1 = focus_1;
    f2 = focus_2;
}

void Ellipse::SetSemiAxisLong(double axis_a)
{
    a = axis_a;
}

void Ellipse::SetSemiAxisShort(double axis_b)
{
    b = axis_b;
}

void Ellipse::GetFocuses(Point &focus_1, Point &focus_2) const
{
    focus_1 = f1;
    focus_2 = f2;
}

double Ellipse::GetSemiAxisLong() const
{
    return a;
}

double Ellipse::GetSemiAxisShort() const
{
    return b;
}
