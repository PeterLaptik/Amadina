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
    m_command_map.insert(std::pair<std::string,Command*>(name, cmd));
}

void CommandDispatcher::RegisterHandler(long handler_id, const std::string &cmd_name)
{
    m_command_handlers.insert(std::pair<long,std::string>(handler_id, cmd_name));
}

Command* CommandDispatcher::GetCommand(const std::string &name, Context *context)
{
    Command *result = nullptr;
    std::map<std::string,Command*>::iterator it = m_command_map.find(name);
    if(it!=m_command_map.end() && context!=nullptr)
        result = it->second->Clone(context);

    return result;
}

Command* CommandDispatcher::GetCommand(long handler_id, Context *context)
{
    std::map<long,std::string>::iterator it = m_command_handlers.find(handler_id);
    if(it==m_command_handlers.end())
        return nullptr;

    return GetCommand(it->second, context);
}
