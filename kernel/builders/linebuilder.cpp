#include "linebuilder.h"
#include "../entities/line.h"
#include <math.h>

LineBuilder::LineBuilder()
{ }

LineBuilder::~LineBuilder()
{ }

bool LineBuilder::AppendPoint(const Point &pt)
{
    points.push_back(pt);
    if(points.size()>1)
        return true;

    return false;
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


LineBuilderOrtho::LineBuilderOrtho()
{ }

LineBuilderOrtho::~LineBuilderOrtho()
{ }

bool LineBuilderOrtho::AppendPoint(const Point &pt)
{
    if(points.size()>0)
    {
        double x0 = points.at(0).GetX();
        double y0 = points.at(0).GetY();
        double x = pt.GetX();
        double y = pt.GetY();
        if(fabs(x0-x)<=fabs(y0-y))
            x = x0;
        else
            y = y0;

        points.push_back(Point(x,y));
        return true;
    }
    points.push_back(pt);
    return false;
}

void LineBuilderOrtho::Redraw(IAdapterDC &dc, double x, double y)
{
    if(points.size()<1)
        return;

    double x0 = points.at(0).GetX();
    double y0 = points.at(0).GetY();

    if(fabs(x0-x)<=fabs(y0-y))
        x = x0;
    else
        y = y0;

    dc.CadDrawLine(points.at(0), Point(x, y));
}

Entity* LineBuilderOrtho::Create()
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

bool LineBuilderOrtho::IsMultiBuild(void) const
{
    return true;
}

