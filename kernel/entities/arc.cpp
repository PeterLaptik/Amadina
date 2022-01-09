#include "arc.h"
#include "../geometry/geometry.h"

Arc::Arc(const Point &center,
            const Point &start,
            const Point &end)
    : m_center(center),
        m_start(start),
        m_end(end)
{
    m_start_angle = geometry::calculate_angle(center.GetX(), center.GetY(),
                                    start.GetX(), start.GetY());
    m_end_angle = geometry::calculate_angle(center.GetX(), center.GetY(),
                                    end.GetX(), end.GetY());
}

Arc::~Arc()
{ }

void Arc::Draw(IAdapterDC &dc)
{
    if(m_start==m_end || m_start==m_center || m_end==m_center)
        return;

    dc.CadDrawArc(m_center, m_start, m_end);
}

void Arc::DrawHighlighted(IAdapterDC &dc)
{
    dc.CadSetColour(Colour(255,0,0));
    Draw(dc);
}

double Arc::DistanceFrom(const Point &pt) const
{
    double x0 = m_center.GetX();
    double y0 = m_center.GetY();
    double x1 = m_start.GetX();
    double y1 = m_start.GetY();
    double x = pt.GetX();
    double y = pt.GetY();
    double m_radius = sqrt((x1 - x0)*(x1 - x0) + (y1 - y0)*(y1 - y0));
    double distance_from_center = sqrt(pow(x-x0,2) + pow(y-y0,2));
    double distance = fabs(distance_from_center - m_radius);

    double angle = geometry::calculate_angle(m_center.GetX(), m_center.GetY(), 
                pt.GetX(), pt.GetY());

    if(!(angle>m_start_angle && angle<m_end_angle && m_start_angle<m_end_angle))
    {
        double distance_1 = geometry::calculate_distance(pt.GetX(), pt.GetY(),
                                m_start.GetX(), m_start.GetY());
        double distance_2 = geometry::calculate_distance(pt.GetX(), pt.GetY(),
                                m_end.GetX(), m_end.GetY());
        distance = std::min(distance_1, distance_2);
    }

    return distance;
}

void Arc::GetSnapPoints(std::vector<Point> &vec) const
{
    vec.push_back(m_start);
    vec.push_back(m_end);
}

void Arc::GetCenterPoints(std::vector<Point> &vec) const
{
    vec.push_back(m_center);
}

void Arc::MoveTo(double delta_x, double delta_y, double delta_z)
{
    m_center.SetX(m_center.GetX() + delta_x);
    m_center.SetY(m_center.GetY() + delta_y);
    m_center.SetZ(m_center.GetZ() + delta_z);
    m_start.SetX(m_start.GetX() + delta_x);
    m_start.SetY(m_start.GetY() + delta_y);
    m_start.SetZ(m_start.GetZ() + delta_z);
    m_end.SetX(m_end.GetX() + delta_x);
    m_end.SetY(m_end.GetY() + delta_y);
    m_end.SetZ(m_end.GetZ() + delta_z);
}

const Point& Arc::GetCenterPoint() const
{
    return m_center;
}

const Point& Arc::GetStartPoint() const
{
    return m_start;
}

const Point& Arc::GetEndPoint() const
{
    return m_end;
}

Entity* Arc::Clone(void)
{
    return new Arc(m_center, m_start, m_end);
}
