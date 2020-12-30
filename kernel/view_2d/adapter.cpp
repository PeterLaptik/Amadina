#include "adapter.h"

Adapter::Adapter()
{ }

Adapter::~Adapter()
{ }


void Adapter::SetCenterPosition(Point point)
{
    m_center_coord = point;
}

void Adapter::SetCenterPosition(double x, double y)
{
    m_center_coord.SetX(x);
    m_center_coord.SetY(y);
    m_center_coord.SetZ(0);
}

void Adapter::SetScreenSize(double width, double height)
{
    m_width = width;
    m_height = height;
}


Point Adapter::GetCenterPosition(void) const
{
    return m_center_coord;
}
