#ifndef CONTEXT_H_INCLUDED
#define CONTEXT_H_INCLUDED

#include "../command/interpreter.h"
#include "../view_2d/screen.h"

class Context
{
    public:
        Context(DrawManager *manager, Screen *screen);
        virtual ~Context();

        void AssignCommand(const std::string &command);
        Screen* GetScreen(void) const;
        DrawManager* GetManager(void) const;

    private:
        DrawManager *m_draw_manager;
        Screen *m_screen;
        Interpreter m_interpreter;
};

#endif // CONTEXT_H_INCLUDED
