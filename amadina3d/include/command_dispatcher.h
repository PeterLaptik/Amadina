#ifndef COMMANDDISPATCHER_H
#define COMMANDDISPATCHER_H

#include "command_abstract.h"
#include <string>
#include <unordered_map>

namespace cad
{
    namespace modeller
    {
        class Context;
        using CommandAbstract = command::CommandAbstract;

        class CommandDispatcher
        {
            public:
                static CommandDispatcher& GetInstance(void);

                virtual ~CommandDispatcher();

                bool AppendCommand(const std::string &name, CommandAbstract* cmd);

                CommandAbstract* GetCommand(const std::string &name, Context *context);

            private:
                CommandDispatcher();
                inline void InitializeDefaultCommands(void);

                std::unordered_map<std::string, CommandAbstract*> m_commands;
        };
    }
}

#endif // COMMANDDISPATCHER_H
