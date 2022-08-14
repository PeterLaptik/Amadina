#ifndef COMMAND_INTERPRETER_H
#define COMMAND_INTERPRETER_H

#include "lexer.h"
#include <vector>

namespace cad
{
    namespace command
    {
        class Interpreter
        {
            public:
                Interpreter();
                virtual ~Interpreter();

                void ParseExpression(std::string expr);

            private:
                void PurgeDelimiters(std::string &expr);
                void Tokenize(const std::string &line);
                bool IsList(const std::string &token);
                void ParseList(const std::string &list_str);

                // Expressions evaluator
                Lexer m_lexer;
                // Keeps all string tokens for a current expression
                std::vector<std::string> m_string_tokens_container;
        };
    }
}
#endif // COMMAND_INTERPRETER_H
