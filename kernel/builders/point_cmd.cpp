#include "point_cmd.h"
#include "../entities/point.h"
#include <iostream>

CmdPoint::CmdPoint(Context *context)
    : Command(context)
{std::cout<<"ctor point"<<std::endl; }

CmdPoint::~CmdPoint()
{ std::cout<<"dtor point"<<std::endl;}


void CmdPoint::Execute()
{
    CMDResult result;
    Point pt;
    result = EnterPoint(&pt);
    m_is_finished = true;
}

Command* CmdPoint::Clone()
{
    return new CmdPoint(GetContext());
}
