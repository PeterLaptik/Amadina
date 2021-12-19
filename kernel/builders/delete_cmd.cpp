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
    CMDResult result;

    result = EnterEntities(&selection);
    if(result!=RES_OK)
        return;

    for(auto i: selection)
        RemoveEntity(i);
}
