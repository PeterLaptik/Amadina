#include "command_dispatcher.h"
#include "commands_names.h"
#include "context.h"
#include "commands_view.h"

using namespace cad::modeller::command;
using namespace cad::modeller::command::names;
using CommandDispatcher = cad::modeller::CommandDispatcher;
using CommandAbstract = cad::modeller::command::CommandAbstract;

CommandDispatcher& CommandDispatcher::GetInstance()
{
    static CommandDispatcher obj;
    return obj;
}

CommandDispatcher::CommandDispatcher()
{
    InitializeDefaultCommands();
}

CommandDispatcher::~CommandDispatcher()
{
    for(auto& cmd: m_commands)
        delete cmd.second;
}

bool CommandDispatcher::AppendCommand(const std::string &name, CommandAbstract* cmd)
{
    if(m_commands.find(name)==m_commands.end())
    {
        delete cmd;
        return false;
    }

    m_commands.insert(std::pair<std::string, CommandAbstract*>(name, cmd));
    return true;
}

CommandAbstract* CommandDispatcher::GetCommand(const std::string &name, Context *context)
{
    auto it = m_commands.find(name);
    if(it==m_commands.end())
        return nullptr;

    return it->second->Clone(context);
}

void CommandDispatcher::InitializeDefaultCommands()
{
    m_commands = {
        {CMD_VIEW_TOP, new CommandViewTop()},
        {CMD_VIEW_BOTTOM, new CommandViewBottom()},
        {CMD_VIEW_LEFT, new CommandViewLeft()},
        {CMD_VIEW_RIGHT, new CommandViewRight()},
        {CMD_VIEW_FRONT, new CommandViewFront()},
        {CMD_VIEW_BACK, new CommandViewBack()}
    };
}
