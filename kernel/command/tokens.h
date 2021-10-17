#ifndef TOKENS_H_INCLUDED
#define TOKENS_H_INCLUDED

#include "../entities/point.h"
#include <string>

class Token
{
    public:
        Token() = delete;

        Token(const std::string &text)
            : m_is_text(true),
                m_is_point(false),
                m_is_number(false),
                m_text(text)
        { }

        Token(const Point &point)
            : m_is_text(false),
                m_is_point(true),
                m_is_number(false),
                m_point(point)
        { }

        Token(double number)
            : m_is_text(false),
                m_is_point(false),
                m_is_number(true),
                m_number(number)
        { }

        ~Token()
        { }

        double GetNumber(void) const {return m_number;}
        std::string GetString(void) const {return m_text;}
        Point GetPoint(void) const {return m_point;}

        bool IsString(void) const {return m_is_text;}
        bool IsNumber(void) const {return m_is_number;}
        bool IsPoint(void) const {return m_is_point;}

    private:
        bool m_is_text;
        bool m_is_point;
        bool m_is_number;

        Point m_point;
        std::string m_text;
        double m_number;
};

#endif // TOKENS_H_INCLUDED
