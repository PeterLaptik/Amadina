#ifndef AMADINA_COMMAND_DISPATCHER_H_INCLUDED
#define AMADINA_COMMAND_DISPATCHER_H_INCLUDED

#include <string>
#include <map>
#include <vector>

namespace cad::command
{
    class BaseCommand;
}

namespace cad::app
{
    class SheetContext;
}

using cad::app::SheetContext;
using cad::command::BaseCommand;

namespace cad::command
{
    class CommandDispatcher
    {
        public:
            CommandDispatcher() = default;

            ~CommandDispatcher() = default;

            bool AddCommand(std::string alias, BaseCommand *cmd);

            void RemoveCommand(std::string alias);

            BaseCommand *GetCommand(std::string cmd) const;



        private:
            std::map<std::string, BaseCommand*> m_commands;
            std::vector<std::string> m_cmd_list;
    };
}

#endif // AMADINA_COMMAND_DISPATCHER_H_INCLUDED
