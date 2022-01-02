#include "interpreter.h"
#include "lexer.h"
#include "exceptions.h"
#include <iostream>
#include <sstream>

// General token delimiter
static const char DELIMITER = ' ';
// Sub-token delimiter. For example, coordinates of the points
static const char SUB_DELIMITER = ',';
// Error messages
static const std::string ERR_NO_MORE_TOKENS = "Out of bound for tokens list.";


Interpreter::Interpreter()
    : m_cursor(0)
{ }


Interpreter::~Interpreter()
{ }


void Interpreter::Interpretate(const std::string &line)
{
    Lexer lexer;
    std::vector<std::string> tokens;

    m_cursor = 0;
    m_tokens.clear();
    // Get primary expressions
    ReadSubExpressions(line, DELIMITER, tokens);
    // Get sub expressions
    std::vector<std::string> sub_tokens;
    for(std::vector<std::string>::iterator it = tokens.begin();
                it!=tokens.end(); ++it)
    {
        sub_tokens.clear();
        ReadSubExpressions(*it, SUB_DELIMITER, sub_tokens);
        if(sub_tokens.size()==1 && IsTextToken(sub_tokens.at(0)))
        {
            Token token(sub_tokens.at(0));
            m_tokens.push_back(token);
        }
        else if(sub_tokens.size()==1)
        {
            double value = lexer.Evaluate(sub_tokens.at(0));
            Token token(value);
            m_tokens.push_back(token);
        }
        else if(sub_tokens.size()==2)
        {
            double x = lexer.Evaluate(sub_tokens.at(0));
            double y = lexer.Evaluate(sub_tokens.at(1));
            Point point(x,y);
            Token token(point);
            m_tokens.push_back(token);
        }
        else if(sub_tokens.size()==3)
        {
            double x = lexer.Evaluate(sub_tokens.at(0));
            double y = lexer.Evaluate(sub_tokens.at(1));
            double z = lexer.Evaluate(sub_tokens.at(2));
            Point point(x,y,z);
            Token token(point);
            m_tokens.push_back(token);
        }
        else
        {
            LexerError error("Error parsing value '" + *it + "'");
            throw error;
        }
    }
}

void Interpreter::ReadSubExpressions(const std::string &line,
                                      const char delimiter,
                                      std::vector<std::string> &tokens)
{
    std::string token;
    std::stringstream sstream(line);

    while(getline(sstream, token, delimiter))
    {
        if(token.size()>0)
            tokens.push_back(token);
    }
}

bool Interpreter::IsTextToken(const std::string &token)
{
    for(size_t i=0; i<token.size(); i++)
        if(isalpha(token.at(i)))
            return true;

    return false;
}

int Interpreter::GetTokensNumber() const
{
    return m_tokens.size();
}

Token Interpreter::GetFirstToken() const
{
    m_cursor = 0;
    return GetNextToken();
}

bool Interpreter::HasNextToken() const
{
    return m_cursor<m_tokens.size();
}

Token Interpreter::GetNextToken() const
{
    if(m_cursor>=m_tokens.size())
        throw LexerError(ERR_NO_MORE_TOKENS);

    return m_tokens.at(m_cursor++);
}
