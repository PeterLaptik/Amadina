#include "point_cmd.h"

CmdPoint::CmdPoint()
{ }

CmdPoint::~CmdPoint()
{ }

void CmdPoint::Execute()
{

}

Command* CmdPoint::Clone()
{
    return new CmdPoint();
}
