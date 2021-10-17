#ifndef CAD_INTERPRETER_H_INCLUDED
#define CAD_INTERPRETER_H_INCLUDED

#include "tokens.h"
#include <string>
#include <vector>

class Interpreter
{
    public:
        Interpreter();
        ~Interpreter();
        void Interpretate(const std::string &line);
        Token GetFirstToken(void) const;
        bool HasNextToken(void) const;
        Token GetNextToken(void) const;
        int GetTokensNumber(void) const;

    protected:

    private:
        std::vector<Token> m_tokens;
        mutable int m_cursor;

        void ReadSubExpressions(const std::string &line,
                                const char delimiter,
                                std::vector<std::string> &tokens);
        bool IsTextToken(const std::string &token);
        void CollapseExpression(const std::string &token);
};

#endif // CAD_INTERPRETER_H_INCLUDED
