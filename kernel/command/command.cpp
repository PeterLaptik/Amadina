#include "command.h"
#include "../context/context.h"
#include "../entities/point.h"
#include "../entities/entity.h"


Command::Command(Context *context)
    : m_is_executing(false),
        m_is_canceled(false),
        m_is_finished(false),
        m_context(context)
{
    m_screen = context->GetScreen();
}

Command::~Command()
{ }

void Command::Terminate()
{
    m_is_finished = true;
    m_is_canceled = true;
}

CMDResult Command::EnterPoint(Point *point)
{
    if(m_is_canceled || m_is_finished)
        return CMDResult::RES_CANCEL;

    m_is_executing = true;
    m_context->GetScreen()->SetState(SCREEN_PICKING_POINT);
    // Call command
    while(m_is_executing && !m_is_canceled)
        ;
    m_context->GetScreen()->SetState(SCREEN_PICKING_POINT);
    return !m_is_canceled ? CMDResult::RES_OK : CMDResult::RES_CANCEL;
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

void Command::SetPoint(const Point &point)
{
    // Assign point
    m_is_executing = false;
}

void Command::SetEntity(Entity *entity)
{

}

void Command::SetEntities(const std::vector<Entity*> &vec)
{

}

