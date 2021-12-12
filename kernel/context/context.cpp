#include "context.h"
#include "../view_2d/screen.h"
#include "../command/command.h"
#include "../command/dispatcher.h"

CommandDispatcher* Context::m_dispatcher = nullptr;

void Context::AssignCommandDispatcher(CommandDispatcher *dispatcher)
{
    m_dispatcher = dispatcher;
}

Context::Context()
    : m_screen(nullptr),
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

void Context::AssignEnvironment(Screen *screen,
                                DrawManager *draw_manager)
{
    m_screen = screen;
    m_draw_manager = draw_manager;
}

void Context::AssignCommand(const std::string &command)
{

}

void Context::ExecuteCommand(Command *command)
{
    if(!m_screen)
    {
        delete command;
        return;
    }

    if(m_current_command)
    {
        m_current_command->Terminate();
        /* TODO check time-out */
        m_cmd_thread->join();
        delete m_cmd_thread;
        delete m_current_command;
        m_screen->SetDataReceiver(nullptr);
    }

    m_current_command = command;
    m_screen->SetDataReceiver(m_current_command);
    m_cmd_thread = new std::thread(&Command::Execute, m_current_command);
}

void Context::Update()
{
    if(!m_current_command)
        return;

    if(m_command_finished!=true)
        return;

    /* TODO check time-out */
    m_cmd_thread->join();

    if(m_current_command->IsAccepted())
    {
        const std::vector<Entity*> created = m_current_command->GetCreated();
        for(auto i: created)
            m_screen->AppendEntity(i);
    }

    // TODO queue
    delete m_cmd_thread;
    delete m_current_command;
    m_cmd_thread = nullptr;
    m_current_command = nullptr;
    m_screen->SetDataReceiver(nullptr);
}

void Context::SetCommandFinished(bool is_finished)
{
    m_command_finished = is_finished;
}

Screen* Context::GetScreen(void) const
{
    return m_screen;
}

DrawManager* Context::GetManager(void) const
{
    return m_draw_manager;
}
