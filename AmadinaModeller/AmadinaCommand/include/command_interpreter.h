#ifndef COMMAND_INTERPRETER_H_INCLUDED
#define COMMAND_INTERPRETER_H_INCLUDED

#include "command_token.h"
#include <string>
#include <vector>
#include <map>

#define DEBUG_OUTPUT_AMADINA_COMMAND_INTERPRETER

namespace cad::command::interpreter
{

    typedef double (*lexer_function_unary_t)(double);
    typedef double (*lexer_function_binary_t)(double, double);


    class CommandInterpreter
    {
        public:
            CommandInterpreter() = default;
            virtual ~CommandInterpreter() = default;

            void ParseExpression(std::string expr);

        private:
            void PurgeDelimiters(std::string &expr);
            void ToLower(std::string &expr);
            void Tokenize(const std::string &line);
            bool IsExpression(const std::string &expr) const;
//            bool IsList(const std::string &token);
//            void ParseList(std::string &list_str);
//
            void ProcessText(std::stringstream &sstream);
            void ProcessList(std::stringstream &sstream, const std::string &line,
                             std::string::size_type &cursor);
            void ProcessString(std::stringstream &sstream, const std::string &line,
                               std::string::size_type &cursor);
//
//            void TryProcessNumberOrExpr(std::string &value);

            void DebugOutput(const std::string &msg, const std::string &txt) const;


            // Expressions evaluator
            //Lexer m_lexer;

            // Keeps all string tokens for a current expression
            std::vector<CommandToken> m_string_tokens_container;

            // Functions holder:
            // Keeps functions names and pointers (unary)
            std::map<std::string, lexer_function_unary_t> m_functions_u;
            // List of available functions, sorted by length
            std::vector<std::string> m_functions_names_u;

            // Keeps functions names and pointers (binary)
            std::map<std::string, lexer_function_binary_t> m_functions_b;
            // List of available functions, sorted by length
            std::vector<std::string> m_functions_names;

            // Constants holder
            // Keeps constants values
            std::map<std::string, double> m_constants;
            // List of available constants, sorted by length
            std::vector<std::string> m_constants_names;

            // List of characters which can appear in math expressions
            static std::vector<char> m_allowed_chars;
        };
}

#endif // COMMAND_INTERPRETER_H_INCLUDED
