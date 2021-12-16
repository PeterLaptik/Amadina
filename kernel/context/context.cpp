#include "context.h"
#include "callable.h"
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
    m_pool(this),
    m_frame(nullptr)
{ }

Context::~Context()
{ }

void Context::AssignCommand(const std::string &command)
{

}

void Context::SetParentFrame(CallableFrame *frame)
{
    m_frame = frame;
}

void Context::ExecuteCommand(Command *command)
{
    m_executor.Execute(command);
}

void Context::TerminateCommand()
{
    m_executor.Terminate();
}

void Context::Update()
{
    bool has_changes = m_executor.Update();
    if(has_changes && m_frame)
        m_frame->SetUndoRedoState(m_pool.HasAccepted(), m_pool.HasDismissed());
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
    return m_screen->GetDrawManager();
}

void Context::Undo()
{
    m_pool.Undo();
    m_screen->ScreenRefresh();
}

void Context::Redo()
{
    m_pool.Redo();
    m_screen->ScreenRefresh();
}

void Context::GetUndoRedoState(bool &undo, bool &redo)
{
    undo = m_pool.HasAccepted();
    redo = m_pool.HasDismissed();
}
