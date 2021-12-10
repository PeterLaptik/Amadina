#include "circle_cmd.h"
#include "../entities/circle.h"

CmdCircle::CmdCircle(Context *context)
        : Command(context),
        m_pt_picked(false)
{ }


CmdCircle::~CmdCircle()
{ }

Command* CmdCircle::Clone(Context *context)
{
    return new CmdCircle(context);
}

void CmdCircle::Run()
{
    CMDResult result;

    result = EnterPoint(&pt1);
    if(result!=RES_OK)
        return;

    m_pt_picked = true;
    result = EnterPoint(&pt2);
    if(result!=RES_OK)
        return;

    double radius = pt1.DistanceFrom(pt2);
    AppendEntity(new Circle(pt1, radius));
}

void CmdCircle::Redraw(IAdapterDC &dc, double x, double y)
{
    if(!m_pt_picked)
        return;

    double radius = pt1.DistanceFrom(Point(x,y));
    dc.CadDrawConstraintLine(pt1.GetX(), pt1.GetY(), x, y);
    dc.CadDrawCircle(pt1, radius);
}
