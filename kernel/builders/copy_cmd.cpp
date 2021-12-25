#include "copy_cmd.h"

CmdCopy::CmdCopy(Context *context)
    : Command(context)
{ }

CmdCopy::~CmdCopy()
{ }

void CmdCopy::Run()
{
    CMDResult result = PrintMessage("Enter objects to copy");
    //CMDResult result = EnterEntities(&selection);

}

Command* CmdCopy::Clone(Context *context)
{
    return new CmdCopy(context);
}

bool CmdCopy::IsMultiCommand()
{
    return false;
}
