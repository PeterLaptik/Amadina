#include "token.h"

using Token = cad::command::Token;

Token::Token(const std::string &value, TokenType type)
    : m_value(value), m_type(type)
    {}

Token::Token(std::string &&value, TokenType type)
    : m_value(std::move(value)), m_type(type)
    {}

Token::~Token()
    {}

bool Token::IsText() const
{
    return m_type==TOKEN_TEXT;
}

bool Token::IsNumeric() const
{
    return m_type==TOKEN_NUMERIC;
}

bool Token::IsList() const
{
    return m_type==TOKEN_LIST;
}
bool Token::IsString() const
{
    return m_type==TOKEN_STRING;
}

std::string Token::GetStringValue() const
{
    return m_value;
}

double Token::GetNumericValue() const
{
    return std::stod(m_value);
}

