#include "command.h"
#include "../entities/point.h"
#include "../entities/entity.h"


Command::Command(StatefulScreen *screen)
    : m_is_executing(false), m_screen(screen)
    { }

Command::~Command()
    { }

void Command::EnterPoint()
{
    m_is_executing = true;
    // Call command
    while(m_is_executing)
        ;

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

