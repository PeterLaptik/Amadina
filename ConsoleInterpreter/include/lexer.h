#ifndef COMMAND_LEXER_H
#define COMMAND_LEXER_H

#include <string>
#include <vector>
#include <map>
#include "lexer_functions.h"

namespace cad
{
    namespace command
    {
        class Lexer
        {
            public:
                Lexer();
                ~Lexer();

                // Parses and evaluates expression
                double Evaluate(std::string expr);

                bool IsExpression(const std::string &expr) const;

                static bool AddFunction(std::string name, lexer_function_t fn);

            private:
                // Pointer to active istringstream-object
                std::istream *m_current_instring;
                double m_number_value;

                enum Token
                {
                    NUMBER,
                    PLUS='+',
                    MINUS='-',
                    MUL='*',
                    DIV='/',
                    LP='(',
                    RP=')',
                    END
                } current_token;

                static std::vector<char> m_allowed_chars;
                static std::vector<std::string> m_allowed_substrings;
                static std::map<std::string,lexer_function_t> m_functions;

                double EvaluateFunctions(std::string &expr);
                Token GetToken();
                double Expression(bool get);
                double Term(bool get);
                double Prim(bool get);
        };



        class LexerError: public std::exception
        {
            public:
                LexerError(const std::string &msg)
                    : m_msg(msg)
                { }

                virtual char const* what() const
                {
                    return m_msg.c_str();
                }

            private:
                std::string m_msg;
        };
    }
}


#endif // COMMAND_LEXER_H
