#include "linebuilder.h"
#include "../entities/line.h"

LineBuilder::LineBuilder()
{ }

LineBuilder::~LineBuilder()
{ }

bool LineBuilder::AppendPoint(const Point &pt)
{
    points.push_back(pt);
    if(points.size()>1)
        return true;
}

void LineBuilder::Redraw(IAdapterDC &dc, double x, double y)
{
    if(points.size()<1)
        return;
    dc.CadDrawLine(points.at(0), Point(x, y));
}

Entity* LineBuilder::Create()
{
    if(points.size()<2)
        return nullptr;

    if(points.at(0)==points.at(1))
    {
        points.clear();
        return nullptr;
    }
    // The last point will be the first point for a new line
    Point pt1 = points.at(0);
    Point pt2 = points.at(1);
    points.clear();
    points.push_back(pt2);

    return new Line(pt1, pt2);
}

bool LineBuilder::IsMultiBuild(void) const
{
    return true;
}
