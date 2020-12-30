#include "default_commands.h"
#include "../builders/linebuilder.h"
#include "../builders/circlebuilder.h"
#include "../builders/squarebuilder.h"

void cad::command::RegisterDefaultCommands(CommandInterpreter &interpreter)
{
    interpreter.RegisterCommand("point", &DrawPoint);
    interpreter.RegisterCommand("line", &DrawLine);
    interpreter.RegisterCommand("circle", &DrawCircle);
    interpreter.RegisterCommand("square", &DrawSquare);
}

void cad::command::DrawPoint(ViewPanel *panel)
{

}

void cad::command::DrawLine(ViewPanel*panel)
{
    panel->CreateEntityByPoints(new LineBuilder());
}

void cad::command::DrawCircle(ViewPanel*panel)
{
    panel->CreateEntityByPoints(new CircleBuilder());
}

void cad::command::DrawSquare(ViewPanel *panel)
{
    panel->CreateEntityByPoints(new SquareBuilder());
}
