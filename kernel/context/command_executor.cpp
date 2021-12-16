#include "command_executor.h"
#include "context.h"
#include "../command/command.h"
#include "../view_2d/screen.h"

CommandExecutor::CommandExecutor(Context *context, CommandPool *pool)
    : m_context(context),
    m_command_pool(pool),
    m_cmd_thread(nullptr),
    m_current_command(nullptr),
    m_command_finished(false)
{ }

CommandExecutor::~CommandExecutor()
{
    // Remove executing thread and command
    // if exist
    if(m_cmd_thread)
    {
        // Stop command executing before delete
        if(m_current_command)
            m_current_command->Terminate();
        m_cmd_thread->join();
        delete m_cmd_thread;
    }

    if(m_current_command)
        delete m_current_command;
}

void CommandExecutor::Execute(Command *cmd)
{
    Screen *screen = m_context->GetScreen();
    if(!screen)
    {
        delete cmd;
        return;
    }
    // Terminate and remove current command if executing
    if(m_current_command)
    {
        m_current_command->Terminate();
        /* TODO check time-out */
        m_cmd_thread->join();
        delete m_cmd_thread;
        delete m_current_command;
        screen->SetDataReceiver(nullptr);
    }
    else if(m_cmd_thread)
    {
        m_cmd_thread->join();
        delete m_cmd_thread;
    }

    // Assign new command
    m_current_command = cmd;
    screen->SetDataReceiver(m_current_command);
    m_cmd_thread = new std::thread(&Command::Execute, m_current_command);
}

bool CommandExecutor::Update()
{
    if(!m_current_command)
        return false;

    if(m_command_finished!=true)
        return false;

    /* TODO check time-out */
    m_cmd_thread->join();

    Screen *screen = m_context->GetScreen();
    Command *clone = nullptr;
    if(m_current_command->IsAccepted() && !m_current_command->IsCanceled())
    {
        const std::vector<Entity*> created = m_current_command->GetCreated();
        for(auto i: created)
            screen->AppendEntity(i);
        m_command_pool->Append(m_current_command);
        if(m_current_command->IsMultiCommand() && !m_current_command->IsCanceled())
            clone = m_current_command->Clone(screen->GetContext());
        m_current_command = nullptr;
    }

    delete m_cmd_thread;
    delete m_current_command;
    m_cmd_thread = nullptr;
    m_current_command = nullptr;
    screen->SetDataReceiver(nullptr);
    if(clone)
        Execute(clone);
    return true;
}

void CommandExecutor::Terminate()
{
    if(m_current_command)
        m_current_command->Terminate();
}

void CommandExecutor::SetCommandFinished(bool is_finished)
{
    m_command_finished = is_finished;
}
