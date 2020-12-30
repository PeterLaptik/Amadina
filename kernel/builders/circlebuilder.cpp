#include "circlebuilder.h"
#include "../entities/circle.h"
#include <math.h>

CircleBuilder::CircleBuilder()
{ }

CircleBuilder::~CircleBuilder()
{ }

bool CircleBuilder::AppendPoint(const Point &pt)
{
    points.push_back(pt);
    if(points.size()>1)
        return true;
}

void CircleBuilder::Redraw(IAdapterDC &dc, double x, double y)
{
    if(points.size()<1)
        return;

    double distance = pow((pow(points.at(0).GetX() - x,2)
                           + pow(points.at(0).GetY() - y,2)),
                          0.5);
    dc.CadDrawCircle(points.at(0), distance);
}

Entity* CircleBuilder::Create()
{
    if(points.size()<2)
        return nullptr;

    if(points.at(0)==points.at(1))
        return nullptr;

    double distance = pow((pow(points.at(0).GetX() - points.at(1).GetX(),2)
                           + pow(points.at(0).GetY() - points.at(1).GetY(),2)),
                          0.5);

    return new Circle(points.at(0), distance);
}
