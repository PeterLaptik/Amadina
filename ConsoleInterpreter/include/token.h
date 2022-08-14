#ifndef COMMAND_TOKEN_H
#define COMMAND_TOKEN_H

#include <string>

namespace cad
{
    namespace command
    {

        enum TokenType
        {
            TEXT,
            NUMERIC,
            LIST,
            STRING
        };


        class Token
        {
            public:
                Token();
                ~Token();

            private:
                void DefineType();

                TokenType m_type;
                std::string m_value;
        };
    }
}

#endif // COMMAND_TOKEN_H
