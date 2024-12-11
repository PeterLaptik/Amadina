#ifndef COMMAND_CONTEXT_H_INCLUDED
#define COMMAND_CONTEXT_H_INCLUDED

#include "base_command.h"
#include <string>
#include <map>

namespace cad::command
{
    class Context
    {
        public:
            Context() = default;
            virtual ~Context() = default;

            void Execute();

            bool AddCommand(const std::string &name, BaseCommand *cmd);
            bool RemoveCommand(const std::string &name);

        private:
            std::map<std::string, BaseCommand*> m_commands;
    };
}

#endif
