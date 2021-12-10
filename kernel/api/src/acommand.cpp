#include "../acommand.h"
#include "../../command/dispatcher.h"
#include "../../builders/point_cmd.h"
#include "../../builders/line_cmd.h"
#include "../../builders/circle_cmd.h"

void register_kernel_commands(CommandDispatcher *dispatcher)
{
    dispatcher->RegisterCommand(new CmdPoint(), "point");
    dispatcher->RegisterCommand(new CmdLine(), "line");
    dispatcher->RegisterCommand(new CmdCircle(), "circle");
}
