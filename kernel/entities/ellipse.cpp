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
    //dc.CadDrawEllipse();
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
    return new Ellipse();
}
