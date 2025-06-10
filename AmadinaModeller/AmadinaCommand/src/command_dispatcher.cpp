#include "command_dispatcher.h"
#include "base_command.h"
#include <algorithm>

using cad::command::BaseCommand;

bool cad::command::CommandDispatcher::AddCommand(std::string alias, BaseCommand *cmd)
{
    std::transform(alias.begin(), alias.end(), alias.begin(), std::toupper);
    auto result = m_commands.insert(std::make_pair(alias, cmd));
    if (result.second)
    {
        m_cmd_list.push_back(alias);
        std::sort(m_cmd_list.begin(), m_cmd_list.end());
    }

    return result.second;
}

void cad::command::CommandDispatcher::RemoveCommand(std::string alias)
{
    std::transform(alias.begin(), alias.end(), alias.begin(), std::toupper);
    auto it = m_commands.find(alias);
    if (it != m_commands.end())
    {
        m_commands.erase(it);
        m_cmd_list.erase(std::remove(m_cmd_list.begin(), m_cmd_list.end(), alias));
    }
}

BaseCommand* cad::command::CommandDispatcher::GetCommand(std::string alias) const
{
    std::transform(alias.begin(), alias.end(), alias.begin(), std::toupper);
    auto it = m_commands.find(alias);
    return it != m_commands.end() ? it->second->Clone() : nullptr;
}
