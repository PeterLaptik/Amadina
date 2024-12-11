#ifndef PARSER_EXCEPTION_H_INCLUDED
#define PARSER_EXCEPTION_H_INCLUDED

#include "string"

namespace cad::command::interpreter
{
    class ParserException: public std::exception
    {
        public:
            explicit ParserException(const std::string &msg) 
                : m_msg(msg)
            { }

            const char *what() const noexcept override
            {
                return m_msg.c_str();
            }

        private:
            std::string m_msg;
    };
}

#endif // !PARSER_EXCEPTION_H_INCLUDED

