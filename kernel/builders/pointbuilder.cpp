#include "pointbuilder.h"

PointBuilder::PointBuilder()
{ }

PointBuilder::~PointBuilder()
{ }

bool PointBuilder::AppendPoint(const Point &pt)
{
    points.push_back(pt);
    return true;
}

void PointBuilder::Redraw(IAdapterDC &dc, double x, double y)
{ }

Entity* PointBuilder::Create()
{
    Point *point = new Point(points.at(0));
    points.clear();
    return point;
}

bool PointBuilder::IsMultiBuild(void) const
{
    return true;
}
