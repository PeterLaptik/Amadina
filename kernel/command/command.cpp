#include "command.h"
#include "../view_2d/screen.h"
#include "../context/context.h"
#include "../entities/point.h"
#include "../entities/entity.h"
#include <thread>

#ifdef __MINGW32__
    #define CMD_WAIT_FOR_INPUT std::this_thread::sleep_for(std::chrono::milliseconds(50))
#else
    #define CMD_WAIT_FOR_INPUT std::this_thread::yield()
#endif // __MINGW32__


Command::Command(Context *context)
    : m_is_executing(false),
        m_is_canceled(false),
        m_is_finished(false),
        m_point(nullptr),
        m_entity(nullptr),
        m_entity_set(nullptr),
        m_context(context),
        m_is_accepted(true)
{ }


Command::~Command()
{
    if(m_is_accepted)
    {
        // Created entities are handled by drawing manager
        for(auto i: m_removed)
        delete i;
    }
    else
    {
        // Removed entities are restored and handled by drawing manager
        for(auto i: m_created)
            delete i;
    }
}

void Command::Execute()
{
    if(!m_context)  // Not allowed execution for prototypes
        return;     // each command has to be executed in a context

    // Context screen availability check has to be preformed at upper level
    // (in command executor). Context with null-screen is not allowed!
    CommandExecutor *executor = m_context->GetExecutor();
    m_context->GetScreen()->SetEntityBuilder(this);
    executor->SetCommandFinished(false);
    m_is_finished = false;
    Run();  // main command loop
    m_is_finished = true;
    executor->SetCommandFinished(true);
    m_context->GetScreen()->SetEntityBuilder(nullptr);
}

CMDResult Command::EnterPoint(Point *point)
{
    if(m_is_finished)
        return CMDResult::RES_CANCEL;

    m_point = point;
    m_is_executing = true;
    m_is_canceled = false;
    m_context->GetScreen()->SetState(SCR_PICKING);

    WaitForInput();

    m_context->GetScreen()->SetState(SCR_NOTHING);
    m_point = nullptr;
    m_is_executing = false;
    return !m_is_canceled && !m_is_finished ? CMDResult::RES_OK : CMDResult::RES_CANCEL;
}

CMDResult Command::EnterEntity(Entity *entity)
{
    if(m_is_canceled || m_is_finished)
        return CMDResult::RES_CANCEL;

    return !m_is_canceled ? CMDResult::RES_OK : CMDResult::RES_CANCEL;
}

CMDResult Command::EnterEntities(std::vector<Entity*> *entity_set)
{
    if(m_is_canceled || m_is_finished)
        return CMDResult::RES_CANCEL;

    return (!m_is_canceled && !m_is_finished) ? CMDResult::RES_OK : CMDResult::RES_CANCEL;
}

void Command::WaitForInput()
{
    while(m_is_executing && !m_is_canceled && !m_is_finished)
        CMD_WAIT_FOR_INPUT;
}

void Command::AppendEntity(Entity *entity)
{
    m_created.push_back(entity);
}

void Command::RemoveEntity(Entity *entity)
{
    m_created.push_back(entity);
}

void Command::SetPoint(const Point &point)
{
    if(!m_point)
        return;

    *m_point = point;
    m_is_executing = false;
}
