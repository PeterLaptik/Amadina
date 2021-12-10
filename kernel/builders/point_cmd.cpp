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
    Point pt;
    CMDResult result;

    result = EnterPoint(&pt);
    if(result==RES_OK)
    {
        Point *p = new Point(pt);
        AppendEntity(p);
    }
}

Command* CmdPoint::Clone(Context *context)
{
    return new CmdPoint(context);
}
