#ifndef CONTEXT_H_INCLUDED
#define CONTEXT_H_INCLUDED

#include "../command/interpreter.h"
#include <thread>

class Screen;
class DrawManager;
class Command;
class CommandDispatcher;

class Context final
{
    public:
        Context();
        ~Context();

        void AssignEnvironment(Screen *screen,
                               DrawManager *draw_manager);
        static void AssignCommandDispatcher(CommandDispatcher *dispatcher);

        void AssignCommand(const std::string &command);
        void ExecuteCommand(Command *command);

        void Update(void);

        void SetCommandFinished(bool is_finished = true);

        Screen* GetScreen(void) const;
        DrawManager* GetManager(void) const;

    private:
        // Environmental objects
        Screen *m_screen;
        DrawManager *m_draw_manager;
        Interpreter m_interpreter;

        // Command executing thread data
        Command *m_current_command;
        std::thread *m_cmd_thread;

        // The flag shows whether a command is finished.
        // Flag can be changed from outside --
        // executing command thread.
        // The value is checked in the 'Update'-method
        // which is to be called on every screen refresh
        volatile bool m_command_finished;

        // Command dispatcher is a common object
        // for all screens and contexts
        // The value should be assigned from outside
        static CommandDispatcher *m_dispatcher;
};

#endif // CONTEXT_H_INCLUDED
