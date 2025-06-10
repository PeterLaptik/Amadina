#ifndef COMMAND_PARSER_H_INCLUDED
#define COMMAND_PARSER_H_INCLUDED

#include "command_token.h"
#include "command_functions_def.h"
#include "command_arguments.h"
#include <string>
#include <map>

namespace cad::command::interpreter
{
    class CommandParser
    {
        public:
            CommandParser() = default;

            ~CommandParser() = default;

            bool ParseCommand(const std::string &command);

            bool IsEmpty() const;

            std::string GetCommand() const;
            
            CommandArguments GetArguments() const;

            std::string GetResultMessage() const;

        private:
            bool TokenizeCommandLine(const std::string &command);
            bool AssignValue(const std::string &command);
            bool IsAssignValueExpression(const std::string &command) const;
            std::string Normalize(const std::string &command) const;

            std::map<std::string, double> m_variables;
            std::map<std::string, double> m_constants;

            std::vector<CommandToken> m_tokens;
            mutable size_t m_token_cursor;
            //static CommandToken m_null_token;

            std::string m_result_message;
    };
}

#endif // COMMAND_PARSER_H_INCLUDED
