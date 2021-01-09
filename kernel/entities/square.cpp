#include "square.h"
#include "line.h"

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
//    double center_x = m_center.GetX();
//    double center_y = m_center.GetY();
//    dc.CadDrawLine(center_x - m_width/2, center_y + m_height/2, center_x + m_width/2 ,center_y + m_height/2);
//    dc.CadDrawLine(center_x - m_width/2, center_y - m_height/2, center_x - m_width/2 ,center_y + m_height/2);
//    dc.CadDrawLine(center_x - m_width/2, center_y - m_height/2, center_x + m_width/2 ,center_y - m_height/2);
//    dc.CadDrawLine(center_x + m_width/2, center_y - m_height/2, center_x + m_width/2 ,center_y + m_height/2);
    line_top.Draw(dc);
    line_bottom.Draw(dc);
    line_left.Draw(dc);
    line_right.Draw(dc);
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
