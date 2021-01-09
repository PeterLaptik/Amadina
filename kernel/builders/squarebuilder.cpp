#include "squarebuilder.h"
#include "../entities/square.h"
#include <math.h>

/////////////////////////////////////////////
// Builds square by center and outer point //
/////////////////////////////////////////////
SquareBuilderByCenter::SquareBuilderByCenter()
{ }

SquareBuilderByCenter::~SquareBuilderByCenter()
{ }

bool SquareBuilderByCenter::AppendPoint(const Point &pt)
{
    points.push_back(pt);
    if(points.size()>1)
        return true;

    return false;
}

void SquareBuilderByCenter::Redraw(IAdapterDC &dc, double x, double y)
{
    if(points.size()<1)
        return;

    double center_x = points.at(0).GetX();
    double center_y = points.at(0).GetY();
    double width = fabs(x - center_x)*2;
    double height = fabs(y - center_y)*2;
    dc.CadDrawLine(center_x - width/2, center_y + height/2, center_x + width/2, center_y + height/2);
    dc.CadDrawLine(center_x - width/2, center_y - height/2, center_x - width/2, center_y + height/2);
    dc.CadDrawLine(center_x - width/2, center_y - height/2, center_x + width/2, center_y - height/2);
    dc.CadDrawLine(center_x + width/2, center_y - height/2, center_x + width/2, center_y + height/2);
    dc.CadDrawConstraintLine(center_x, center_y, x, y);
}

Entity* SquareBuilderByCenter::Create()
{
    if(points.size()<2)
        return nullptr;

    if(points.at(0)==points.at(1))
        return nullptr;

    double center_x = points.at(0).GetX();
    double center_y = points.at(0).GetY();
    double width = fabs(points.at(1).GetX() - center_x)*2;
    double height = fabs(points.at(1).GetY() - center_y)*2;

    return new Square(points.at(0), width, height);
}

/////////////////////////////////
// Builds square by two points //
/////////////////////////////////
SquareBuilderByPoints::SquareBuilderByPoints()
{ }

SquareBuilderByPoints::~SquareBuilderByPoints()
{ }

bool SquareBuilderByPoints::AppendPoint(const Point &pt)
{
    points.push_back(pt);
    if(points.size()>1)
        return true;

    return false;
}

void SquareBuilderByPoints::Redraw(IAdapterDC &dc, double x, double y)
{
    if(points.size()<1)
        return;

    double start_x = points.at(0).GetX();
    double start_y = points.at(0).GetY();
    dc.CadDrawLine(start_x, start_y, x, start_y);
    dc.CadDrawLine(x, start_y, x, y);
    dc.CadDrawLine(x, y, start_x, y);
    dc.CadDrawLine(start_x, y, start_x, start_y);
    dc.CadDrawConstraintLine(start_x, start_y, x, y);
}

Entity* SquareBuilderByPoints::Create()
{
    if(points.size()<2)
        return nullptr;

    if(points.at(0)==points.at(1))
        return nullptr;

    double pt1_x = points.at(0).GetX();
    double pt1_y = points.at(0).GetY();
    double pt2_x = points.at(1).GetX();
    double pt2_y = points.at(1).GetY();
    double width = fabs(pt1_x - pt2_x);
    double height = fabs(pt1_y - pt2_y);
    double center_x = (pt1_x < pt2_x ? pt1_x : pt2_x) + width/2;
    double center_y = (pt1_y < pt2_y ? pt1_y : pt2_y) + height/2;
    return new Square(Point(center_x, center_y), width, height);
}
