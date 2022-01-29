#include "paste_cmd.h"

CmdPaste::CmdPaste(Context *context)
    : Command(context)
{ }

CmdPaste::~CmdPaste()
{
    for(auto i: m_clones)
        delete i;
}

void CmdPaste::Run(void)
{
    CMDResult result;
    if(GetContext()->GetClipBoard()->IsEmpty())
    {
        PrintMessage("Clipboard is empty.");
        result = RES_ERROR;
        return;
    }

    PrintMessage("Pick point to paste.");
    m_base_point = GetContext()->GetClipBoard()->GetBasePoint();
    // Clone objects to paste
    auto objects = GetContext()->GetClipBoard()->GetObjects();
    for(auto i: objects)
        m_clones.push_back(i->Clone());

    result = EnterPoint(&m_insert_point);
    if(result!=RES_OK)
        return;

    int delta_x = m_insert_point.GetX() - m_base_point.GetX();
    int delta_y = m_insert_point.GetY() - m_base_point.GetY();
    int delta_z = m_insert_point.GetZ() - m_base_point.GetZ();
    for(auto i: m_clones)
    {
        i->MoveTo(delta_x, delta_y, delta_z);
        AppendEntity(i);
    }
    m_clones.clear();
}

void CmdPaste::Redraw(IAdapterDC &dc, double x, double y)
{
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

Command* CmdPaste::Clone(Context *context)
{
    return new CmdPaste(context);
}

bool CmdPaste::IsMultiCommand()
{
    return true;
}
