#ifndef COMMAND_TOKEN_H_INCLUDED
#define COMMAND_TOKEN_H_INCLUDED

#include <string>

namespace cad::command::interpreter
{
    enum TokenType
    {
        TOKEN_CMD_TEXT,
        TOKEN_CMD_NUMERIC,
        TOKEN_CMD_LIST,
        TOKEN_CMD_STRING
    };

    class CommandToken final
    {
        public:
            CommandToken() = delete;
            CommandToken(const std::string &value, TokenType type);
            CommandToken(std::string &&value, TokenType type);
            ~CommandToken(void);

            bool IsText(void) const;
            bool IsNumeric(void) const;
            bool IsList(void) const;
            bool IsString(void) const;

            std::string GetStringValue(void) const;
            double GetNumericValue(void) const;


        private:
            std::string m_value;
            TokenType m_type;
    };
}

#endif // COMMAND_TOKEN_H_INCLUDED
