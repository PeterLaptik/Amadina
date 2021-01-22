#include "square.h"
#include "line.h"
#include <algorithm>

Square::Square()
{ }

Square::Square(Point pt, double width, double height)
        : m_center(pt), m_width(width), m_height(height)
{
    double center_x = m_center.GetX();
    double center_y = m_center.GetY();
    line_top.SetStartPoint(Point(center_x - m_width/2, center_y + m_height/2));
    line_top.SetEndPoint(Point(center_x + m_width/2, center_y + m_height/2));
    line_bottom.SetStartPoint(Point(center_x - m_width/2, center_y - m_height/2));
    line_bottom.SetEndPoint(Point(center_x + m_width/2, center_y - m_height/2));
    line_left.SetStartPoint(Point(center_x - m_width/2, center_y - m_height/2));
    line_left.SetEndPoint(Point(center_x - m_width/2, center_y + m_height/2));
    line_right.SetStartPoint(Point(center_x + m_width/2, center_y - m_height/2));
    line_right.SetEndPoint(Point(center_x + m_width/2, center_y + m_height/2));
}

Square::~Square()
{ }

void Square::Draw(IAdapterDC &dc)
{
    line_top.Draw(dc);
    line_bottom.Draw(dc);
    line_left.Draw(dc);
    line_right.Draw(dc);
}

void Square::DrawHighlighted(IAdapterDC &dc)
{
    dc.CadSetColour(Colour(255,0,0));
    line_top.DrawHighlighted(dc);
    line_bottom.DrawHighlighted(dc);
    line_left.DrawHighlighted(dc);
    line_right.DrawHighlighted(dc);
}

double Square::DistanceFrom(const Point &pt) const
{
    double vertical = std::min(line_left.DistanceFrom(pt), line_right.DistanceFrom(pt));
    double horizontal = std::min(line_top.DistanceFrom(pt), line_bottom.DistanceFrom(pt));
    return std::min(vertical, horizontal);
}

void Square::GetSnapPoints(std::vector<Point> &vec) const
{
    double center_x = m_center.GetX();
    double center_y = m_center.GetY();
    vec.push_back(Point(center_x + m_width/2 ,center_y + m_height/2));
    vec.push_back(Point(center_x - m_width/2 ,center_y + m_height/2));
    vec.push_back(Point(center_x + m_width/2 ,center_y - m_height/2));
    vec.push_back(Point(center_x - m_width/2 ,center_y - m_height/2));
}

void Square::GetCenterPoints(std::vector<Point> &vec) const
{
    double center_x = m_center.GetX();
    double center_y = m_center.GetY();
    vec.push_back(m_center);
    vec.push_back(Point(center_x ,center_y + m_height/2));
    vec.push_back(Point(center_x ,center_y - m_height/2));
    vec.push_back(Point(center_x + m_width/2 ,center_y));
    vec.push_back(Point(center_x - m_width/2 ,center_y));
}

void Square::GetPrimitives(std::vector<Entity*> &vec)
{
    vec.push_back(&line_top);
    vec.push_back(&line_bottom);
    vec.push_back(&line_left);
    vec.push_back(&line_right);
}
