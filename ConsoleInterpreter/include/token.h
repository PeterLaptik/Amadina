#ifndef COMMAND_TOKEN_H
#define COMMAND_TOKEN_H

#include <string>

namespace cad
{
    namespace command
    {
        enum TokenType
        {
            TOKEN_TEXT,
            TOKEN_NUMERIC,
            TOKEN_LIST,
            TOKEN_STRING
        };

        class Token
        {
            public:
                Token(const std::string &value, TokenType type);
                Token(std::string &&value, TokenType type);
                ~Token(void);

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
}

#endif // COMMAND_TOKEN_H
