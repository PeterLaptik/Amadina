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
    }
    else if(m_cmd_thread)
    {
        // Additional check: must be unreachable case
        // (thread without assigned command is not allowed)
        m_cmd_thread->join();
        delete m_cmd_thread;
    }

    // Assign new command
    m_current_command = cmd;
    m_cmd_thread = new std::thread(&Command::Execute, m_current_command);
}

// Works only for existing finished command
// Updates entities in drawing manager there is
// successfully executed command.
// Deletes command and command thread,
// creates new command + thread
// and starts them (for multi-command builders).
// Returns true if drawing manager was updated
bool CommandExecutor::Update()
{
    if(!m_current_command)
        return false;

    if(!m_command_finished)
        return false;

    /* TODO check time-out */
    m_cmd_thread->join();

    // If command is multi-command
    // then new clone must be created for execution.
    // It must be repeated until execution is not canceled explicitly
    Command *clone = nullptr;

    Screen *screen = m_context->GetScreen();
    if(m_current_command->IsAccepted() && !m_current_command->IsCanceled())
    {
        // Append created entities to a drawing manager
        const std::vector<Entity*> created = m_current_command->GetCreated();
        for(auto i: created)
            screen->AppendEntity(i);
        // Save command
        m_command_pool->Append(m_current_command);
        // Create clone (if the command is multi-command)
        if(m_current_command->IsMultiCommand() && !m_current_command->IsCanceled())
            clone = m_current_command->Clone(screen->GetContext());
        m_current_command = nullptr;
    }

    delete m_cmd_thread;
    delete m_current_command;
    m_cmd_thread = nullptr;
    m_current_command = nullptr;
    // Next execution if multi-command
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
