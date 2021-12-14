#include "context.h"
#include "../view_2d/screen.h"
#include "../command/command.h"
#include "../command/dispatcher.h"

CommandDispatcher* Context::m_dispatcher = nullptr;

void Context::AssignCommandDispatcher(CommandDispatcher *dispatcher)
{
    m_dispatcher = dispatcher;
}

Context::Context(Screen *screen)
    : m_executor(this, &m_pool),
    m_screen(screen),
    m_draw_manager(nullptr),
    m_current_command(nullptr),
    m_cmd_thread(nullptr),
    m_command_finished(false)
{ }

Context::~Context()
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

void Context::AssignCommand(const std::string &command)
{

}

void Context::ExecuteCommand(Command *command)
{
    m_executor.Execute(command);
}

void Context::Update()
{
    m_executor.Update();
}


CommandExecutor* Context::GetExecutor()
{
    return &m_executor;
}

Screen* Context::GetScreen(void) const
{
    return m_screen;
}

DrawManager* Context::GetManager(void) const
{
    return m_draw_manager;
}
