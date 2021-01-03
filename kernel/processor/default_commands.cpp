#include "default_commands.h"
#include "../builders/linebuilder.h"
#include "../builders/circlebuilder.h"
#include "../builders/squarebuilder.h"
#include "../builders/pointbuilder.h"

void cad::command::RegisterDefaultCommands(CommandInterpreter &interpreter)
{
    interpreter.RegisterCommand(CMD_POINT, &DrawPoint);
    interpreter.RegisterCommand(CMD_LINE, &DrawLine);
    interpreter.RegisterCommand(CMD_LINE_ORTHOGONAL, &DrawLineOrtho);
    interpreter.RegisterCommand(CMD_CIRCLE, &DrawCircle);
    interpreter.RegisterCommand(CMD_SQUARE_CENTER, &DrawSquareCenter);
    interpreter.RegisterCommand(CMD_SQUARE, &DrawSquareFrame);
}

void cad::command::DrawPoint(ViewPanel *panel)
{
    panel->CreateEntityByPoints(new PointBuilder());
}

void cad::command::DrawLine(ViewPanel *panel)
{
    panel->CreateEntityByPoints(new LineBuilder());
}

void cad::command::DrawLineOrtho(ViewPanel *panel)
{
    panel->CreateEntityByPoints(new LineBuilderOrtho());
}

void cad::command::DrawCircle(ViewPanel *panel)
{
    panel->CreateEntityByPoints(new CircleBuilder());
}

void cad::command::DrawSquareCenter(ViewPanel *panel)
{
    panel->CreateEntityByPoints(new SquareBuilderByCenter());
}

void cad::command::DrawSquareFrame(ViewPanel *panel)
{
    panel->CreateEntityByPoints(new SquareBuilderByPoints());
}
