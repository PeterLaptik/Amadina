#include "command.h"
#include "../context/context.h"
#include "../entities/point.h"
#include "../entities/entity.h"


Command::Command(Context *context)
    : m_is_executing(false),
        m_context(context)
{
    m_screen = context->GetScreen();
}

Command::~Command()
{ }

void Command::EnterPoint()
{
    m_is_executing = true;
    m_context->GetScreen()->SetState(SCREEN_PICKING_POINT);
    // Call command
    while(m_is_executing)
        ;
    m_context->GetScreen()->SetState(SCREEN_PICKING_POINT);
}

void Command::EnterEntity()
{

}

void Command::EnterEntities()
{

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

