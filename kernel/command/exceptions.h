#ifndef EXCEPTIONS_H_INCLUDED
#define EXCEPTIONS_H_INCLUDED

#ifdef __GNUC__
    #define NO_EXCEPT_VALUE _GLIBCXX_USE_NOEXCEPT
#else
    #define NO_EXCEPT_VALUE
#endif // __GNUC__

class LexerError: public std::exception
{
    public:
        LexerError()
            : m_text(DEFAULT_TEXT)
        { }

        LexerError(const std::string text)
            : m_text(text)
        { }

        ~LexerError()
        { }

        virtual const char* what() const NO_EXCEPT_VALUE
        {
            return m_text.c_str();
        }

    private:
        const std::string DEFAULT_TEXT = "Lexer error.";
        std::string m_text;
};

#endif // EXCEPTIONS_H_INCLUDED
