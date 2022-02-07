#ifndef CONTEXT_H_INCLUDED
#define CONTEXT_H_INCLUDED

#include "command_pool.h"
#include "command_executor.h"
#include "clipboard.h"
#include "../command/interpreter.h"
#include "../api/exports.h"
#include <thread>
#include <mutex>

class Screen;
class DrawManager;
class Command;
class CommandDispatcher;
class CallableFrame;

///\brief Screen panel information holder and indirect command executor.
/// The class appears a facade for other objects
/// which implement main functionality for interacting
/// between logical and graphical system parts
class DLL_EXPORT Context final
{
    public:
        Context(Screen *screen);

        ~Context(void);

        /// Assigns command dispatcher.
        /// The static method need to be called once
        /// to assign initialized command dispatcher
        /// for all contexts
        static void AssignCommandDispatcher(CommandDispatcher *dispatcher);

        /// Assigns command / message from console.
        /// The message is parsed by interpreter and evaluated
        ///\command - message string
        void AssignInput(const std::string &command);

        bool HasInput(void);
        Token GetInput(void);

        /// Starts command execution.
        /// If other command is executing
        /// then it will be terminated.
        ///\param command - command to execute.
        /// The command is handled by the context
        void ExecuteCommand(Command *command);

        void TerminateCommand(void);

        /// Callback for screen updating on command accept.
        /// Should be called after each screen state change
        void Update();
        void Undo(void);
        void Redo(void);
        void GetUndoRedoState(bool &undo, bool &redo);

        CommandExecutor* GetExecutor(void);

        void SetParentFrame(CallableFrame *frame);

        ///\brief Sends text message to a console of a main GUI-frame.
        /// Default implementation calls 'PrintMessage'-method
        /// of a 'CallableFrame'-object.
        /// This method can be called from another thread (command-thread).
        /// Thread safety of the call must be provided
        /// by a 'CallableFrame'-object.
        ///\param msg - message
        ///\see CallableFrame
        void PrintMessage(const std::string &msg);

        // Updates screen
        void UpdateScreen(void);

        /// Returns context's screen
        Screen* GetScreen(void) const;

        void ClearSelection(void);

        ClipBoard* GetClipBoard(void);


    private:
        CommandExecutor m_executor;

        // Accepted and dismissed commands
        CommandPool m_pool;

        // Environmental objects:
        Screen *m_screen;


        CallableFrame *m_frame;

        // Command interpreter:
        // parses data inputed from a console
        Interpreter m_interpreter;

        // Clipboard
        // Keeps selected elements as a list of clones
        ClipBoard m_clipboard;

        // Executing command
//        Command *m_current_command;

        // Each command executes in a separate thread:
//        std::thread *m_cmd_thread;

        // The flag shows whether a command is finished.
        // Flag can be changed from outside --
        // executing command thread.
        // The value is checked in the 'Update'-method
        // which is to be called on every screen refresh
//        volatile bool m_command_finished;

        // Command dispatcher is a common object
        // for all screens and contexts
        // The value should be assigned from outside
        static CommandDispatcher *m_dispatcher;
};

#endif // CONTEXT_H_INCLUDED
