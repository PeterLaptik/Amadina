#include "command_token.h"
#include <algorithm>

cad::command::interpreter::CommandToken::CommandToken(const std::string &value, TokenType type)
    : m_str(value), m_type(type)
{
    if (m_type == TOKEN_CMD_TEXT)
        TextToLower();
}

cad::command::interpreter::CommandToken::CommandToken(std::string &&value, TokenType type)
    : m_str(std::move(value)), m_type(type)
{
    if (m_type == TOKEN_CMD_TEXT)
        TextToLower();
}

cad::command::interpreter::CommandToken::CommandToken(double value)
    : m_num(value), m_type(TOKEN_CMD_NUMERIC)
{ }

cad::command::interpreter::CommandToken::CommandToken(const std::vector<double> &list)
    : m_list(list), m_type(TOKEN_CMD_LIST)
{
    m_list_size = m_list.size();
}

cad::command::interpreter::CommandToken::CommandToken(std::vector<double> &&list)
    : m_list(std::move(list)), m_type(TOKEN_CMD_LIST)
{
    m_list_size = m_list.size();
}

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

const std::string& cad::command::interpreter::CommandToken::GetStringValue() const
{
    return m_str;
}

double cad::command::interpreter::CommandToken::GetNumericValue() const
{
    return m_num;
}

double cad::command::interpreter::CommandToken::Get(int i) const
{
    return m_list.at(i);
}

bool cad::command::interpreter::CommandToken::IsListEmpty() const
{
    return m_list_size == 0;
}

size_t cad::command::interpreter::CommandToken::GetListSize() const
{
    return m_list.size();
}

void cad::command::interpreter::CommandToken::TextToLower()
{
    std::transform(m_str.begin(), m_str.end(), m_str.begin(), 
        [] (auto ch) {
            return std::tolower(ch);
        });
}
