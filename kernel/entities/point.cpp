#include "point.h"
#include <math.h>

bool Point::operator==(const Point &pt)
{
    return (pt.GetX()==x)&&(pt.GetY()==y)&&(pt.GetZ()==z);
}

void Point::Draw(IAdapterDC &dc)
{
    dc.CadDrawPoint(*this);
}

double Point::GetDistanceBetween(const Point &pt1, const Point &pt2)
{
    double x1 = pt1.GetX();
    double y1 = pt1.GetY();
    double z1 = pt1.GetZ();

    double x2 = pt2.GetX();
    double y2 = pt2.GetY();
    double z2 = pt2.GetZ();

    return pow(pow(fabs(x1 - x2), 2)
               + pow(fabs(y1 - y2), 2)
               + pow(fabs(z1 - z2), 2),
               0.5);
}
