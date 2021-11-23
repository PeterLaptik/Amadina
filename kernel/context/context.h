#ifndef CONTEXT_H_INCLUDED
#define CONTEXT_H_INCLUDED

#include "../command/interpreter.h"
#include "../view_2d/screen.h"

class Context final
{
    public:
        Context();
        ~Context();

        void AssignEnvironment(StatefullScreen *screen, DrawManager *draw_manager);
        void AssignCommand(const std::string &command);

        StatefullScreen* GetScreen(void) const;
        DrawManager* GetManager(void) const;

    private:
        StatefullScreen *m_screen;
        DrawManager *m_draw_manager;
        Interpreter m_interpreter;
};

#endif // CONTEXT_H_INCLUDED
