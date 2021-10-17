#include "context.h"

Context::Context(DrawManager *manager, Screen *screen)
{ }

Context::~Context()
{
    delete m_screen;
    delete m_draw_manager;
}

void Context::AssignCommand(const std::string &command)
{

}

Screen* Context::GetScreen(void) const
{
    return m_screen;
}

DrawManager* Context::GetManager(void) const
{
    return m_draw_manager;
}
