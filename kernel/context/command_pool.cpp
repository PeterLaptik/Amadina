#include "command_pool.h"
#include "context.h"
#include "../command/command.h"
#include "../view_2d/screen.h"

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

    // Update drawing manager
    Screen *screen = m_context->GetScreen();
    const std::vector<Entity*> created = command->GetCreated();
    for(auto i: created)
        screen->AppendEntity(i);
    const std::vector<Entity*> removed = command->GetRemoved();
    for(auto i: removed)
        screen->DeleteEntity(i);

    m_accepted.push_back(command);
}

void CommandPool::Undo()
{
    if(m_accepted.size()<1)
        return;

    Command *cmd = m_accepted.back();
    cmd->Dismiss();

    Screen *screen = m_context->GetScreen();
    const std::vector<Entity*>& created = cmd->GetCreated();
    for(auto entity: created)
        screen->DeleteEntity(entity);

    const std::vector<Entity*>& removed = cmd->GetRemoved();
    for(auto entity: removed)
        screen->AppendEntity(entity);

    m_dismissed.push_back(cmd);
    m_accepted.pop_back();
}

void CommandPool::Redo()
{
    if(m_dismissed.size()<1)
        return;

    Command *cmd = m_dismissed.back();
    cmd->Accept();

    Screen *screen = m_context->GetScreen();;
    const std::vector<Entity*>& created = cmd->GetCreated();
    for(auto entity: created)
        screen->AppendEntity(entity);

    const std::vector<Entity*>& removed = cmd->GetRemoved();
    for(auto entity: removed)
        screen->DeleteEntity(entity);

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

bool CommandPool::HasAcceptedCommands()
{
    return m_accepted.size();
}

bool CommandPool::HasDismissedCommands()
{
    return m_dismissed.size();
}
