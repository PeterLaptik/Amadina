#ifndef COMMAND_EXECUTOR_H_INCLUDED
#define COMMAND_EXECUTOR_H_INCLUDED

#include <thread>

class Command;
class Context;
class CommandPool;

class CommandExecutor final
{
    public:
        CommandExecutor(Context *context, CommandPool *pool);

        ~CommandExecutor(void);

         void Execute(Command *cmd);

         void Terminate(void);

         bool Update(void);

         /// Sets command state to finish.
         /// Callback for command thread
         ///\param is_finished - is command finished
         void SetCommandFinished(bool is_finished = true);

    private:
        // Executor's context and command pool
        Context *m_context;
        CommandPool *m_command_pool;

        // Current command thread
        std::thread *m_cmd_thread;

        // Current command
        Command *m_current_command;

        // The flag shows whether a command is finished.
        // Flag can be changed from outside --
        // executing command thread.
        // The value is checked in the 'Update'-method
        // which is to be called on every screen refresh
        volatile bool m_command_finished;
};

#endif // COMMAND_EXECUTOR_H_INCLUDED
