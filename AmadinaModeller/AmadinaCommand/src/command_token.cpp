#include "command_token.h"

cad::command::interpreter::CommandToken::CommandToken(const std::string &value, TokenType type)
    : m_value(value), m_type(type)
{}

cad::command::interpreter::CommandToken::CommandToken(std::string &&value, TokenType type)
    : m_value(std::move(value)), m_type(type)
{}

cad::command::interpreter::CommandToken::~CommandToken()
{}

bool cad::command::interpreter::CommandToken::IsText() const
{
    return m_type==TOKEN_CMD_TEXT;
}

bool cad::command::interpreter::CommandToken::IsNumeric() const
{
    return m_type==TOKEN_CMD_NUMERIC;
}

bool cad::command::interpreter::CommandToken::IsList() const
{
    return m_type==TOKEN_CMD_LIST;
}
bool cad::command::interpreter::CommandToken::IsString() const
{
    return m_type==TOKEN_CMD_STRING;
}

std::string cad::command::interpreter::CommandToken::GetStringValue() const
{
    return m_value;
}

double cad::command::interpreter::CommandToken::GetNumericValue() const
{
    return std::stod(m_value);
}
