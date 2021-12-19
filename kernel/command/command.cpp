#include "command.h"
#include "../view_2d/screen.h"
#include "../context/context.h"
#include "../entities/point.h"
#include "../entities/entity.h"
#include <thread>

/**
* TODO: Recheck screen updating
* Current implementation -- 'm_context->GetScreen()->RefreshScreen()' (see below).
* The implementation calls 'Refresh'-method of a screen panel,
* i.e. makes the call from a worker thread which can be harmful
**/

#ifdef __MINGW32__
    #define CMD_WAIT_FOR_INPUT std::this_thread::sleep_for(std::chrono::milliseconds(50))
#else
    #define CMD_WAIT_FOR_INPUT std::this_thread::yield()
#endif // __MINGW32__


Command::Command(Context *context)
    : m_is_finished(false),
        m_is_executing(false),
        m_is_canceled(false),
        m_point(nullptr),
        m_entity(nullptr),
        m_entity_set(nullptr),
        m_context(context),
        m_is_accepted(true)
{ }


Command::~Command()
{
    if(m_is_accepted && !m_is_canceled)
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

bool Command::IsMultiCommand(void) const
{
    return false;
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

    m_entity_set = entity_set;
    m_is_executing = true;
    m_is_canceled = false;
    m_context->GetScreen()->SetState(SCR_SELECTING);

    WaitForInput();

    m_context->GetScreen()->SetState(SCR_NOTHING);
    m_entity_set = nullptr;
    m_is_executing = false;
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
    m_removed.push_back(entity);
}

void Command::SetPoint(const Point &point)
{
    if(!m_point)
    {
        m_is_canceled = true;
        return;
    }

    *m_point = point;
    m_is_executing = false;
}

void Command::SetEntities(const std::vector<Entity*> &selection)
{

    if(!m_entity_set)
    {
        m_is_canceled = true;
        return;
    }

    for(auto i: selection)
        m_entity_set->push_back(i);

    m_is_executing = false;
}

Context* Command::GetContext()
{
    return m_context;
}

const std::vector<Entity*>& Command::GetCreated() const
{
    return m_created;
}

const std::vector<Entity*>& Command::GetRemoved() const
{
    return m_removed;
}

void Command::Terminate()
{
    m_is_finished = true;
    m_is_canceled = true;
}

bool Command::IsFinished() const
{
    return m_is_finished;
}

bool Command::IsCanceled() const
{
    return m_is_canceled;
}

void Command::Accept()
{
    m_is_accepted = true;
}

void Command::Dismiss()
{
    m_is_accepted = false;
}

bool Command::IsAccepted() const
{
    return m_is_accepted;
}
