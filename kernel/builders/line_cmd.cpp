#include "line_cmd.h"
#include "../entities/line.h"

CmdLine::CmdLine(Context *context)
        : Command(context),
        m_pt1_picked(false)
{ }

CmdLine::~CmdLine()
{ }

Command* CmdLine::Clone(Context *context)
{
    return new CmdLine(context);
}

void CmdLine::Run()
{
    CMDResult result;

    result = EnterPoint(&pt1);
    if(result!=RES_OK)
        return;

    m_pt1_picked = true;
    result = EnterPoint(&pt2);
    if(result!=RES_OK)
        return;

    AppendEntity(new Line(pt1, pt2));
    Line *line = new Line(pt1, pt2);
}

void CmdLine::Redraw(IAdapterDC &dc, double x, double y)
{
    if(!m_pt1_picked)
        return;

    dc.CadDrawLine(pt1, Point(x,y));
}
