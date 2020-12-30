#include "square.h"

Square::Square()
{ }

Square::Square(Point pt, double width, double height)
        : m_center(pt), m_width(width), m_height(height)
{ }

Square::~Square()
{ }

void Square::Draw(IAdapterDC &dc)
{
    double center_x = m_center.GetX();
    double center_y = m_center.GetY();
    dc.CadDrawLine(center_x - m_width/2, center_y + m_height/2, center_x + m_width/2 ,center_y + m_height/2);
    dc.CadDrawLine(center_x - m_width/2, center_y - m_height/2, center_x - m_width/2 ,center_y + m_height/2);
    dc.CadDrawLine(center_x - m_width/2, center_y - m_height/2, center_x + m_width/2 ,center_y - m_height/2);
    dc.CadDrawLine(center_x + m_width/2, center_y - m_height/2, center_x + m_width/2 ,center_y + m_height/2);

}

void Square::GetSnapPoints(std::vector<std::pair<Entity*,Point>> &vec)
{
    double center_x = m_center.GetX();
    double center_y = m_center.GetY();
    vec.push_back(std::pair<Entity*,Point>(this, Point(center_x + m_width/2 ,center_y + m_height/2)));
    vec.push_back(std::pair<Entity*,Point>(this, Point(center_x - m_width/2 ,center_y + m_height/2)));
    vec.push_back(std::pair<Entity*,Point>(this, Point(center_x + m_width/2 ,center_y - m_height/2)));
    vec.push_back(std::pair<Entity*,Point>(this, Point(center_x - m_width/2 ,center_y - m_height/2)));
}

void Square::GetCenterPoints(std::vector<std::pair<Entity*, Point>> &vec)
{
    double center_x = m_center.GetX();
    double center_y = m_center.GetY();
    vec.push_back(std::pair<Entity*,Point>(this, m_center));
    vec.push_back(std::pair<Entity*,Point>(this, Point(center_x ,center_y + m_height/2)));
    vec.push_back(std::pair<Entity*,Point>(this, Point(center_x ,center_y - m_height/2)));
    vec.push_back(std::pair<Entity*,Point>(this, Point(center_x + m_width/2 ,center_y)));
    vec.push_back(std::pair<Entity*,Point>(this, Point(center_x - m_width/2 ,center_y)));
}
