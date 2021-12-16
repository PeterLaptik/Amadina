#include "command_pool.h"
#include "context.h"
#include "../command/command.h"
#include "../processor/drawmanager.h"


CommandPool::CommandPool(Context *context)
    : m_context(context)
{ }

CommandPool::~CommandPool()
{ }

void CommandPool::Append(Command *command)
{
    if(!command)
        return;

    for(auto i: m_dismissed)
        delete i;
    m_dismissed.clear();

    command->Accept();
    m_accepted.push_back(command);
}

void CommandPool::Undo()
{
    if(m_accepted.size()<1)
        return;

    Command *cmd = m_accepted.back();
    cmd->Dismiss();

    DrawManager *mgr = m_context->GetManager();
    const std::vector<Entity*>& created = cmd->GetCreated();
    for(auto entity: created)
        mgr->DeleteEntity(entity);

    const std::vector<Entity*>& removed = cmd->GetRemoved();
    for(auto entity: removed)
        mgr->AddEntity(entity);

    m_dismissed.push_back(cmd);
    m_accepted.pop_back();
}

void CommandPool::Redo()
{
    if(m_dismissed.size()<1)
        return;

    Command *cmd = m_dismissed.back();
    cmd->Accept();

    DrawManager *mgr = m_context->GetManager();
    const std::vector<Entity*>& created = cmd->GetCreated();
    for(auto entity: created)
        mgr->AddEntity(entity);

    const std::vector<Entity*>& removed = cmd->GetRemoved();
    for(auto entity: removed)
        mgr->DeleteEntity(entity);

    m_accepted.push_back(cmd);
    m_dismissed.pop_back();
}

void CommandPool::Clear()
{
    for(auto i: m_dismissed)
        delete i;
    m_dismissed.clear();

    for(auto i: m_accepted)
        delete i;
    m_accepted.clear();
}

bool CommandPool::HasAccepted()
{
    return m_accepted.size();
}

bool CommandPool::HasDismissed()
{
    return m_dismissed.size();
}
