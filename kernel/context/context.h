#ifndef CONTEXT_H_INCLUDED
#define CONTEXT_H_INCLUDED

#include "command_pool.h"
#include "../command/interpreter.h"
#include "../api/exports.h"
#include <thread>

class Screen;
class DrawManager;
class Command;
class CommandDispatcher;

///\brief Screen information holder and command executor
class DLL_EXPORT Context final
{
    public:
        Context();

        ~Context();

        /// Assigns a screen for the context.
        /// Each context can work only for defined screen / draw manager.
        /// Context without assigned screen does not work properly
        void AssignEnvironment(Screen *screen,
                               DrawManager *draw_manager);

        /// Assigns command dispatcher.
        /// The static method neet to be called once
        /// to assign initialized command dispatcher
        static void AssignCommandDispatcher(CommandDispatcher *dispatcher);

        /// Assigns command / message from console.
        /// The message is parsed by interpreter and evaluated
        ///\command - message string
        void AssignCommand(const std::string &command);

        /// Starts command execution.
        /// If other command is executing
        /// then it will be terminated.
        ///\param command - command to execute.
        /// The command is handled by the context
        void ExecuteCommand(Command *command);

        /// Callback for screen updating on command accept.
        /// Should be called after each screen state change
        void Update();

        /// Sets command state to finish.
        /// Callback for command thread
        ///\param is_finished - is command finished
        void SetCommandFinished(bool is_finished = true);

        /// Returns context's screen
        Screen* GetScreen(void) const;

        /// Returns context screen's draw manager
        DrawManager* GetManager(void) const;

    private:
        // Accepted and dismissed commands
        CommandPool m_pool;

        // Environmental objects:
        Screen *m_screen;
        DrawManager *m_draw_manager;

        // Command interpreter:
        // parses data inputed from a console
        Interpreter m_interpreter;

        // Executing command
        Command *m_current_command;

        // Each command executes in a separate thread:
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
