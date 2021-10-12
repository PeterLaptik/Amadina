#ifndef LEXER_H_INCLUDED
#define LEXER_H_INCLUDED

#include <string>
#include <sstream>

class Lexer
{
    public:
        Lexer();
        ~Lexer();
        // Parse and evaluate expression
        double Evaluate(const std::string &expr);

    private:
        std::istream *instring;
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
        };
        Token current_token;

        Token GetToken();
        double Expression(bool get);
        double Term(bool get);
        double Prim(bool get);
        void Skip();
};

#endif // LEXER_H_INCLUDED
