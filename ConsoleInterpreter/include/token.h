#ifndef COMMAND_TOKEN_H
#define COMMAND_TOKEN_H

#include <string>

namespace cad
{
    namespace command
    {
        struct Token
        {
            enum TokenType
            {
                TOKEN_TEXT,
                TOKEN_NUMERIC,
                TOKEN_LIST,
                TOKEN_STRING
            } type;

            Token()
                : type(TOKEN_TEXT), value("")
                {}

            std::string value;
        };
    }
}

#endif // COMMAND_TOKEN_H
