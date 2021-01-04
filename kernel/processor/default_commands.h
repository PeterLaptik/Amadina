#ifndef DEFAULT_COMMANDS_H_INCLUDED
#define DEFAULT_COMMANDS_H_INCLUDED

#include "interpreter.h"

namespace cad
{
    namespace command
    {
        // Default commands
        const std::string CMD_POINT = "point";
        const std::string CMD_LINE = "line";
        const std::string CMD_LINE_ORTHOGONAL = "line_ortho";
        const std::string CMD_SQUARE = "square";
        const std::string CMD_SQUARE_CENTER = "square_center";
        const std::string CMD_CIRCLE = "circle";

        void RegisterDefaultCommands(CommandInterpreter &interpreter);

        // Command callbacks
        void DrawPoint(ViewPanel *panel);
        void DrawLine(ViewPanel *panel);
        void DrawLineOrtho(ViewPanel *panel);
        void DrawCircle(ViewPanel *panel);
        void DrawSquareCenter(ViewPanel *panel);
        void DrawSquareFrame(ViewPanel *panel);
    }

    namespace preferences
    {
        const std::string PREF_GRID_SHOW = "grid_show";
        const std::string PREF_SNAP_GRID = "snap_grid";
    }
}


#endif // DEFAULT_COMMANDS_H_INCLUDED
