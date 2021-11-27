#include "point_cmd.h"
#include "../entities/point.h"
#include <iostream>

CmdPoint::CmdPoint(Context *context)
    : Command(context)
{ }

CmdPoint::~CmdPoint()
{ }

void CmdPoint::Run()
{
    CMDResult result;
    Point pt;
    result = EnterPoint(&pt);
    AppendEntity(new Point(pt));
}

Command* CmdPoint::Clone()
{
    return new CmdPoint(GetContext());
}
