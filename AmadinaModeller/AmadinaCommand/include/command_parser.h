#ifndef COMMAND_PARSER_H_INCLUDED
#define COMMAND_PARSER_H_INCLUDED

#include "command_functions_def.h"
#include <string>
#include <map>

namespace cad::command::interpreter
{
    class CommandParser
    {
        public:
            CommandParser() = default;

            ~CommandParser() = default;

            bool ParseCommand(std::string command);

            std::string GetResultMessage() const;

        private:
            bool IsAssignValueExpression(const std::string &command) const;
            bool AssignValue(std::string command);
            std::pair<bool,double> EvaluateMathExpression(std::string math_expression);

            std::map<std::string, double> m_variables;
            std::string m_result_message;
    };
}

#endif // COMMAND_PARSER_H_INCLUDED
