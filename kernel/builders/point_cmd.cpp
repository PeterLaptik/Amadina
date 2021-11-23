#include "point_cmd.h"
#include <iostream>

CmdPoint::CmdPoint(Context *context)
    : Command(context)
{std::cout<<"ctor point"<<std::endl; }

CmdPoint::~CmdPoint()
{ std::cout<<"dtor point"<<std::endl;}


void CmdPoint::Execute()
{
    EnterPoint();
    std::cout<<"start point"<<std::endl;
    for(;;){}
    std::cout<<"end point"<<std::endl;
}

Command* CmdPoint::Clone()
{
    return new CmdPoint(GetContext());
}
