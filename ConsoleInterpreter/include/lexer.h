#ifndef COMMAND_LEXER_H
#define COMMAND_LEXER_H

#include <string>

namespace cad
{
    namespace command
    {
        class Lexer
        {
            public:
                Lexer();
                ~Lexer();

                // Parse and evaluate expression
                double Evaluate(const std::string &expr);

            private:
                // Pointer to active istringstream-object
                std::istream *m_instring_pt;
                double number_value;

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
