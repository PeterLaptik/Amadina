#ifndef DISPATCHER_H_INCLUDED
#define DISPATCHER_H_INCLUDED

#include "uicommands.h"
#include <string>
#include <map>


class Command;

///\brief Global command registrar and dispatcher.
/// Keeps mappings for commands objects:
/// names-commands and handlers-commands pairs.
/// Commands have to be able to be cloned:
/// the dispatcher keeps a command prototype
/// and does not return command itself but it's clone.
class CommandDispatcher
{
    public:
        CommandDispatcher();
        virtual ~CommandDispatcher();

        ///\brief Registers command in store.
        ///\param cmd - command object
        ///\param cmd_name - command name (string value for console)
        virtual void RegisterCommand(Command *cmd, const std::string &cmd_name);

        ///\brief Registers command handler in store.
        /// Command handler is an object which can call the command.
        /// For example: button, menu item, etc.
        ///\param handler_id - handler id
        ///\param cmd_name - command name (string value for console)
        virtual void RegisterHandler(long handler_id, const std::string &cmd_name);

        ///\brief Returns command object by command name
        /// The command object is not handled by the dispatcher
        /// after returning. So it should be deleted manually
        virtual Command* GetCommand(const std::string &name);

        ///\brief Returns command object by handler id
        /// The command object is not handled by the dispatcher
        /// after returning. So it should be deleted manually
        virtual Command* GetCommand(long handler_id);

    private:
        std::map<std::string, Command*> m_command_map;  // 'command name - command object' pairs
        std::map<long,std::string> m_command_handlers;  // 'handler-id - command name' pairs
};

#endif // DISPATCHER_H_INCLUDED
