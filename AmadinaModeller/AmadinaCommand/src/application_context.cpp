#include "application_context.h"

bool cad::app::ApplicationContext::AddCommand(const std::string &name, BaseCommand *cmd)
{
    return m_cmd_dispatcher.AddCommand(name, cmd);
}

BaseCommand* cad::app::ApplicationContext::GetCommand(std::string alias)
{
    return m_cmd_dispatcher.GetCommand(alias);
}

void cad::app::ApplicationContext::RemoveCommand(const std::string &name)
{
    m_cmd_dispatcher.RemoveCommand(name);
}
