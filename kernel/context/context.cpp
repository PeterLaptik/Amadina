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
    m_frame(nullptr),
    m_clipboard(this)
{ }

Context::~Context()
{ }

void Context::AssignInput(const std::string &command)
{
    try
    {
        m_interpreter.Interpretate(command);
        Token token = m_interpreter.GetFirstToken();
        if(token.IsString())
        {
            std::string cmd_name = token.GetString();
            Command *cmd = m_dispatcher->GetCommand(cmd_name, this);
            if(cmd)
                ExecuteCommand(cmd);
        }
        else if(token.IsPoint())
        {
            Point pt = token.GetPoint();
            m_executor.SendPoint(pt);
        }
    }
    catch(const std::exception &e)
    {
        m_frame->PrintMessage(e.what());
    }

}

bool Context::HasInput()
{
    return m_interpreter.HasNextToken();
}

Token Context::GetInput()
{
    return m_interpreter.GetNextToken();
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
        m_frame->SetUndoRedoState(m_pool.HasAcceptedCommands(), m_pool.HasDismissedCommands());
}

void Context::PrintMessage(const std::string &msg)
{
    m_frame->PrintMessage(msg);
}


CommandExecutor* Context::GetExecutor()
{
    return &m_executor;
}

Screen* Context::GetScreen(void) const
{
    return m_screen;
}

ClipBoard* Context::GetClipBoard()
{
    return &m_clipboard;
}


void Context::Undo()
{
    m_pool.Undo();
    m_screen->RefreshScreen();
}

void Context::Redo()
{
    m_pool.Redo();
    m_screen->RefreshScreen();
}

void Context::GetUndoRedoState(bool &undo, bool &redo)
{
    undo = m_pool.HasAcceptedCommands();
    redo = m_pool.HasDismissedCommands();
}
