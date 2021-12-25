#include "../api/acommand.h"
#include "dispatcher.h"
#include "../builders/point_cmd.h"
#include "../builders/line_cmd.h"
#include "../builders/circle_cmd.h"
#include "../builders/delete_cmd.h"
#include "../builders/copy_cmd.h"

void register_kernel_commands(CommandDispatcher *dispatcher)
{
    dispatcher->RegisterCommand(new CmdPoint(), "point");
    dispatcher->RegisterCommand(new CmdLine(), "line");
    dispatcher->RegisterCommand(new CmdCircle(), "circle");
    dispatcher->RegisterCommand(new CmdDelete(), "delete");
    dispatcher->RegisterCommand(new CmdCopy(), "copy");
}
