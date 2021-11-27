#include "command.h"
#include "../view_2d/screen.h"
#include "../context/context.h"
#include "../entities/point.h"
#include "../entities/entity.h"
#include <thread>


Command::Command(Context *context)
    : m_is_executing(false),
        m_is_canceled(false),
        m_is_finished(false),
        m_point(nullptr),
        m_entity(nullptr),
        m_entity_set(nullptr),
        m_context(context),
        m_is_accepted(true)
{
    m_screen = context->GetScreen();
}

Command::~Command()
{
    if(!m_is_accepted)
    {
        for(auto i: m_created)
            delete i;

        for(auto i: m_removed)
            delete i;
    }
}

void Command::Execute()
{
    if(!m_context)  // Not allowed execution for prototypes
        return;     // each command has to be executed in a context

    m_context->SetCommandFinished(false);
    m_is_finished = false;
    Run();
    m_is_finished = true;
    m_context->SetCommandFinished(true);
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
        std::this_thread::yield();
}


void Command::AppendEntity(Entity *entity)
{
    m_created.push_back(entity);
}

void Command::RemoveEntity(Entity *entity)
{
    m_created.push_back(entity);
}
#include<wx/msgdlg.h>
void Command::SetPoint(const Point &point)
{
    if(!m_point)
        return;
    wxMessageBox("ffff");
    *m_point = point;
    m_is_executing = false;
}
