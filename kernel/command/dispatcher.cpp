#include "dispatcher.h"
#include "command.h"

CommandDispatcher::CommandDispatcher()
{ }

CommandDispatcher::~CommandDispatcher()
{
    for(std::map<std::string,Command*>::iterator it=m_command_map.begin();
                it!=m_command_map.end(); ++it)
    {
        delete it->second;
    }
}

void CommandDispatcher::RegisterCommand(Command *cmd, const std::string &name)
{
    m_command_map.insert(std::pair<std::string,Command*>(name,cmd));
}

Command* CommandDispatcher::GetCommand(const std::string &name)
{
    Command *result = nullptr;
    std::map<std::string,Command*>::iterator it = m_command_map.find(name);
    if(it!=m_command_map.end())
        result = it->second->Clone();

    return result;
}
