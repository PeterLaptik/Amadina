#include "context.h"
#include "command_dispatcher.h"
#include "command_abstract.h"

using Context = cad::modeller::Context;
using CommandDispatcher = cad::modeller::CommandDispatcher;
using CommandAbstract = cad::modeller::command::CommandAbstract;

Context::Context(Handle(V3d_View) view, Handle(AIS_ViewCube) view_cube)
    : m_view(view), m_view_cube(view_cube)
{ }

Context::~Context()
{ }

void Context::RunCommand(const std::string &cmd_name)
{
    CommandDispatcher &dispatcher = CommandDispatcher::GetInstance();
    CommandAbstract *cmd = dispatcher.GetCommand(cmd_name, this);
    if(cmd==nullptr)
        return;

    cmd->Execute();
    delete cmd;
}

Handle(V3d_View) Context::GetView()
{
    return m_view;
}

Handle(AIS_ViewCube) Context::GetViewCube()
{
    return m_view_cube;
}
