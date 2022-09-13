#ifndef COMMAND_LEXER_H
#define COMMAND_LEXER_H

#include <string>
#include <vector>
#include <map>
#include "lexer_math_functions.h"

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
                double Evaluate(std::string expression);

                bool IsExpression(const std::string &expr) const;

                static bool AddFunction(std::string name, lexer_function_t fn);
                static bool AddConstant(std::string name, double value);

                static void UseDegreesForAngles(bool use_degrees);

            private:
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

                Token GetToken();
                void EvaluateFunctions(std::string &expr);
                void ReplaceConstants(std::string &expr);
                double Expression(bool get);
                double Term(bool get);
                double Prim(bool get);
                static void ToLowerCase(std::string &str);

                // Pointer to active istringstream-object
                std::istream *m_current_instring;
                double m_number_value;

                static std::vector<char> m_allowed_chars;

                // Function holder:
                // Keeps functions names and pointers
                static std::map<std::string,lexer_function_t> m_functions;
                // List of available functions, sorted by length
                static std::vector<std::string> m_functions_names;

                static std::map<std::string,double> m_constants;
                static std::vector<std::string> m_constants_names;

                // Emergency flag.
                // Counts 'GetToken'-method recursive calls
                // If number of calls cross the available limit,
                // then 'Bad expression'-exception is thrown
                unsigned int m_call_counter;

                // Flag which shows whether functions and constants
                // were added to function/constant holders.
                // False-value by default.
                static bool m_functions_initilized;
        };



        class LexerError: public std::exception
        {
            public:
                LexerError(const std::string &msg)
                    : m_msg(msg)
                { }

                virtual char const* what() const
                { return m_msg.c_str(); }

            private:
                std::string m_msg;
        };
    }
}


#endif // COMMAND_LEXER_H
