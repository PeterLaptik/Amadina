#include "copy_cmd.h"
#include "../entities/point.h"


CmdCopy::CmdCopy(Context *context)
    : Command(context)
{ }

CmdCopy::~CmdCopy()
{
    //for(auto i: m_clones)
        //delete i;
}

void CmdCopy::Run()
{
    CMDResult result;

    PrintMessage("Enter objects to copy");
    result = EnterEntities(&m_selection);
    if(result!=RES_OK)
        return;

    PrintMessage("Enter base point");
    result = EnterPoint(&m_base_point);
    if(result!=RES_OK)
        return;

    GetContext()->ClearSelection();
    GetContext()->GetClipBoard()->AddObjects(m_selection);
    GetContext()->GetClipBoard()->SetBasePoint(m_base_point);
}

Command* CmdCopy::Clone(Context *context)
{
    return new CmdCopy(context);
}

bool CmdCopy::IsMultiCommand()
{
    return false;
}
