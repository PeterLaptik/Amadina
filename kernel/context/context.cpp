#include "context.h"

Context::Context()
{ }

Context::~Context()
{ }

void Context::AssignEnvironment(StatefullScreen *screen, DrawManager *draw_manager)
{
    m_screen = screen;
    m_draw_manager = draw_manager;
}

void Context::AssignCommand(const std::string &command)
{

}

StatefullScreen* Context::GetScreen(void) const
{
    return m_screen;
}

DrawManager* Context::GetManager(void) const
{
    return m_draw_manager;
}
