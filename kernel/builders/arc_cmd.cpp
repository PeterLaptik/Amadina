#include "arc_cmd.h"
#include "../entities/arc.h"

CmdArc::CmdArc(Context *context)
    : Command(context),
    m_pt_center_picked(false),
    m_pt_1_picked(false)
{ }

CmdArc::~CmdArc()
{ }

void CmdArc::Run()
{
    CMDResult result;

    PrintMessage("Pick center point");
    result = EnterPoint(&pt_center);
    if(result!=RES_OK)
        return;

    m_pt_center_picked = true;
    PrintMessage("Pick start point");
    result = EnterPoint(&pt_start);
    if(result!=RES_OK)
        return;

    m_pt_1_picked = true;
    PrintMessage("Pick end point");
    result = EnterPoint(&pt_end);
    if(result!=RES_OK)
        return;

    AppendEntity(new Arc(pt_center, pt_start, pt_end));
}

void CmdArc::Redraw(IAdapterDC &dc, double x, double y)
{
    if(!m_pt_center_picked)
        return;

    if(!m_pt_1_picked)
    {
        dc.CadDrawConstraintLine(pt_center.GetX(), pt_center.GetY(), x, y);
    }
    else
    {
        Point current_point(x,y);
        dc.CadDrawConstraintLine(pt_center.GetX(), pt_center.GetY(), x, y);
        dc.CadDrawArc(pt_center, pt_start, current_point);
    }
}

Command* CmdArc::Clone(Context *context)
{
    return new CmdArc(context);
}
