#include "commands/create_sketch.h"

using cad::command::CommandArguments;

bool cad::command::CreateSketch::Execute(SheetContext *ctx, CommandArguments &args)
{
    size_t args_num = args.GetSize();
    if (args_num < 2)
    {
        m_err_msg = "Too few arguments.";
        return false;
    }

    Point pt = GetPointFromList(args.GetArg(0));

    return true;
}

cad::command::BaseCommand* cad::command::CreateSketch::Clone()
{
    return new CreateSketch();
}
