#include "copy_cmd.h"
#include "../entities/point.h"


CmdCopy::CmdCopy(Context *context)
    : Command(context),
    m_is_showing(false)
{ }

CmdCopy::~CmdCopy()
{
    for(auto i: m_clones)
        delete i;
}

void CmdCopy::Run()
{
    CMDResult result;

    PrintMessage("Enter objects to copy");
    result = EnterEntities(&m_selection);
    if(result!=RES_OK)
        return;

    for(auto i: m_selection)
        m_clones.push_back(i->Clone());

    PrintMessage("Enter base point");
    result = EnterPoint(&m_base_point);
    if(result!=RES_OK)
        return;

    m_is_showing = true;
    PrintMessage("Enter insert point");
    result = EnterPoint(&m_insert_point);
    if(result!=RES_OK)
        return;

//    int delta_x = m_insert_point.GetX() - m_base_point.GetX();
//    int delta_y = m_insert_point.GetY() - m_base_point.GetY();
//    int delta_z = m_insert_point.GetZ() - m_base_point.GetZ();
    for(auto i: m_clones)
    {
        //i->MoveTo(delta_x, delta_y, delta_z);
        AppendEntity(i);
    }
}

void CmdCopy::Redraw(IAdapterDC &dc, double x, double y)
{
    if(!m_is_showing)
        return;

    int delta_x = x - m_base_point.GetX();
    int delta_y = y - m_base_point.GetY();
    m_base_point = Point(m_base_point.GetX()+delta_x,
                         m_base_point.GetY()+delta_y);
    for(auto i: m_clones)
    {
        i->MoveTo(delta_x, delta_y);
        i->Draw(dc);
    }
}

Command* CmdCopy::Clone(Context *context)
{
    return new CmdCopy(context);
}

bool CmdCopy::IsMultiCommand()
{
    return false;
}
