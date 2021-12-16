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
    CmdLine *clone = new CmdLine(context);
    // Continue from previous point
    // if the command is cloned from executed command
    // (multi-command mode)
    if(m_pt1_picked)
    {
        clone->pt1 = pt2;
        clone->m_pt1_picked = true;
    }
    return clone;
}

void CmdLine::Run()
{
    CMDResult result;

    // Continue from previous point
    // For multi-command mode
    if(!m_pt1_picked)
    {
        result = EnterPoint(&pt1);
        if(result!=RES_OK)
            return;
    }

    m_pt1_picked = true;
    result = EnterPoint(&pt2);
    if(result!=RES_OK)
        return;

    AppendEntity(new Line(pt1, pt2));
}

void CmdLine::Redraw(IAdapterDC &dc, double x, double y)
{
    if(!m_pt1_picked)
        return;

    dc.CadDrawLine(pt1, Point(x,y));
}

bool CmdLine::IsMultiCommand() const
{
    return true;
}
