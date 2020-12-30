#ifndef DEFAULT_COMMANDS_H_INCLUDED
#define DEFAULT_COMMANDS_H_INCLUDED

#include "interpreter.h"

namespace cad
{
    namespace command
    {
        void RegisterDefaultCommands(CommandInterpreter &interpreter);
        void DrawPoint(ViewPanel *panel);
        void DrawLine(ViewPanel *panel);
        void DrawCircle(ViewPanel *panel);
        void DrawSquare(ViewPanel *panel);
    }
}


#endif // DEFAULT_COMMANDS_H_INCLUDED
