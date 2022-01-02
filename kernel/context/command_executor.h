#ifndef COMMAND_EXECUTOR_H_INCLUDED
#define COMMAND_EXECUTOR_H_INCLUDED

#include <thread>

class Command;
class Context;
class CommandPool;
class Point;

///\brief Class for executing command objects in separate threads.
/// Receives and handles command object and keeps command executing thread.
/// Only one command and command thread can exist at once:
/// if a new command was assigned from outside while unfinished command exists,
/// unfinished command and its thread will be terminated and deleted.
/// Successfully finished commands append to command pool and their threads are deleted.
/// The class does not handle objects creating by commands, these objects
/// have to be handled by commands their self.
/// Command executing means executing 'Execute'-method of command object in a separate thread.
class CommandExecutor
{
    public:
        /// Constructor.
        ///\param context - context for command execution
        ///\param pool - command pool for finished commands
        CommandExecutor(Context *context, CommandPool *pool);

        CommandExecutor() = delete;

        ~CommandExecutor(void);

        ///\brief Main execution procedure.
        /// Since command is received by the method,
        /// it will be handled by CommandExecutor
        /// and should not be changed or deleted from outside
        ///\param cmd - command to execute
        void Execute(Command *cmd);

        ///\brief Tries to stop command execution.
        void Terminate(void);

        ///\brief Checks whether a command is finished.
        /// If the command has finished successfully then
        /// it will be added to a command pool, its thread
        /// will be stopped and deleted. If the command was
        /// canceled then the both command and its thread
        /// will be deleted.
        /// The method is a callback for outside objects.
        /// Should be called on external objects updating,
        /// events, and interactions which can lead to command finishing
        /// in order to add/remove objects of screen as quick as command finished.
        ///\return true - if command finished (no matter successfully or not),
        /// false - if command is not finished or there is no executing command
        bool Update(void);

        /// Sets command state to finish.
        /// Callback for command thread
        ///\param is_finished - is command finished
        void SetCommandFinished(bool is_finished = true);

        void SendPoint(const Point &point);

    private:
        // Executor's context
        Context *m_context;
        // Executors command pool:
        // keeps commands for undo-redo procedures
        CommandPool *m_command_pool;

        // Current command thread
        std::unique_ptr<std::thread> ptr_thread;
        // Current command
        std::unique_ptr<Command> ptr_cmd;

        // The flag shows whether a command is finished.
        // Flag can be changed from outside --
        // executing command thread.
        // The value is checked in the 'Update'-method
        // which is to be called on every screen refresh
        volatile bool m_command_finished;
};

#endif // COMMAND_EXECUTOR_H_INCLUDED
