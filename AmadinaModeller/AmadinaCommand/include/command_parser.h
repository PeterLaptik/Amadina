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

            bool ParseCommand(const std::string &command);

            std::string GetResultMessage() const;

        private:
            bool IsAssignValueExpression(const std::string &command) const;
            bool AssignValue(const std::string &command);
            void EvaluateAssignmentExpression(const std::string &math_expression);
            double EvaluateMathExpression(const std::string &math_expression);
            void PutVariable(const std::string &var_name, double var_value);
            void PutConstant(const std::string &const_name, double const_value);
            bool DoesConstantExist(const std::string &constant_name) const;

            std::map<std::string, double> m_variables;
            std::map<std::string, double> m_constants;
            std::string m_result_message;
    };
}

#endif // COMMAND_PARSER_H_INCLUDED
