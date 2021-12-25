#include "delete_cmd.h"

CmdDelete::CmdDelete(Context *context)
        : Command(context)
{ }


CmdDelete::~CmdDelete()
{ }


Command* CmdDelete::Clone(Context *context)
{
    return new CmdDelete(context);
}

void CmdDelete::Run()
{
    PrintMessage("Enter objects to delete:");
    CMDResult result = EnterEntities(&selection);
    if(result!=RES_OK)
        return;

    for(auto i: selection)
        RemoveEntity(i);

    std::string msg = "Removed "
        + std::to_string(selection.size())
        + " objects.";
    PrintMessage(msg);
}
