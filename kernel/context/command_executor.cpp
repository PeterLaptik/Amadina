#include "command_executor.h"
#include "context.h"
#include "../command/command.h"


CommandExecutor::CommandExecutor(Context *context, CommandPool *pool)
    : m_context(context),
    m_command_pool(pool),
    m_command_finished(false)
{ }


CommandExecutor::~CommandExecutor()
{
    if(ptr_cmd)
    {
        ptr_cmd->Terminate();
        ptr_thread->join();
    }
}

// Starts command execution
void CommandExecutor::Execute(Command *cmd)
{
    Screen *screen = m_context->GetScreen();
    if(!screen)
    {
        delete cmd;
        return;
    }
    // Terminate and remove current command if executing
    if(ptr_cmd)
    {
        ptr_cmd->Terminate();
        /* TODO check time-out */
        ptr_thread->join();
        ptr_thread.reset(nullptr);
        ptr_cmd.reset(nullptr);
    }
    else if(ptr_thread)
    {
        // Additional check: must be unreachable case
        // (thread without assigned command is not allowed)
        ptr_thread->join();
        ptr_thread.reset(nullptr);
    }

    if(cmd==nullptr)
        return;

    // Assign new command
    ptr_cmd.reset(cmd);
    ptr_thread.reset(new std::thread(&Command::Execute, ptr_cmd.get()));
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
    if(!ptr_cmd)
        return false;

    if(!m_command_finished)
        return false;

    /* TODO check time-out */
    ptr_thread->join();

    // If command is multi-command
    // then new clone must be created for execution.
    // It must be repeated until execution is not canceled explicitly
    Command *clone = nullptr;
    if(!ptr_cmd->IsCanceled())
    {
        // Create clone (if the command is multi-command)
        if(ptr_cmd->IsMultiCommand() && !ptr_cmd->IsCanceled())
            clone = ptr_cmd->Clone(m_context);
        // Save command
        m_command_pool->Append(ptr_cmd.release());
    }
    ptr_thread.reset(nullptr);
    ptr_cmd.reset(nullptr);

    // Next execution for multi-command
    if(clone)
        Execute(clone);

    return true;
}

void CommandExecutor::Terminate()
{
    if(ptr_cmd && !ptr_cmd->IsFinished())
        ptr_cmd->Terminate();
}

void CommandExecutor::SetCommandFinished(bool is_finished)
{
    m_command_finished = is_finished;
}
