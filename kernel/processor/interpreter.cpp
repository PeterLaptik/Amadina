#include "interpreter.h"

CommandInterpreter::CommandInterpreter()
        : m_active_panel(nullptr)
{ }

CommandInterpreter::~CommandInterpreter()
{ }


void CommandInterpreter::RegisterCommand(const std::string &name, command_function cmd)
{
    m_commands.emplace(std::pair<std::string,command_function>(name, cmd));
}


void CommandInterpreter::ExecuteCommand(const std::string &name)
{
    if(!m_active_panel)
        return;

    std::unordered_map<std::string,command_function>::const_iterator it = m_commands.find(name);
    if(it==m_commands.end())
        return;

    command_function cmd = it->second;
    cmd(m_active_panel);
}

void CommandInterpreter::SetActivePanel(ViewPanel *panel)
{
    m_active_panel = panel;
}

void CommandInterpreter::ResetActivePanel(void)
{
    m_active_panel = nullptr;
}
