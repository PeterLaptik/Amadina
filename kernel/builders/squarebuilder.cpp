#include "squarebuilder.h"
#include "../entities/square.h"
#include <math.h>

SquareBuilder::SquareBuilder()
{ }

SquareBuilder::~SquareBuilder()
{ }

bool SquareBuilder::AppendPoint(const Point &pt)
{
    points.push_back(pt);
    if(points.size()>1)
        return true;
}

void SquareBuilder::Redraw(IAdapterDC &dc, double x, double y)
{
    if(points.size()<1)
        return;

    double center_x = points.at(0).GetX();
    double center_y = points.at(0).GetY();
    double width = fabs(x - center_x)*2;
    double height = fabs(y - center_y)*2;
    dc.CadDrawLine(center_x - width/2, center_y + height/2, center_x + width/2 ,center_y + height/2);
    dc.CadDrawLine(center_x - width/2, center_y - height/2, center_x - width/2 ,center_y + height/2);
    dc.CadDrawLine(center_x - width/2, center_y - height/2, center_x + width/2 ,center_y - height/2);
    dc.CadDrawLine(center_x + width/2, center_y - height/2, center_x + width/2 ,center_y + height/2);
}

Entity* SquareBuilder::Create()
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
