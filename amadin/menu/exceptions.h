#ifndef EXCEPTIONS_H_INCLUDED
#define EXCEPTIONS_H_INCLUDED

#include <exception>
#include <string>

#ifdef __GNUC__
    #define NO_EXCEPT_VALUE _GLIBCXX_USE_NOEXCEPT
#else
    #define NO_EXCEPT_VALUE
#endif // __GNUC__

///\brief The exception occurs if the command name trying
/// to be registered already exists.
///\see AmadinMenu
class CommandExists: public std::exception
{
    public:
        CommandExists(const std::string &exception)
            : m_message(PREFIX + exception)
        { }

        virtual ~CommandExists()
        { }

        virtual char const* what() const NO_EXCEPT_VALUE
        {
            return m_message.c_str();
        }

    private:
        const char *PREFIX = "Command exists: ";
        std::string m_message;
};


///\brief The exception is thrown if a menu section does not exist
class MenuDoesNotExist: public std::exception
{
    public:
        MenuDoesNotExist(const std::string &menu)
            : m_message(PREFIX + menu)
        { }

        virtual ~MenuDoesNotExist()
        { }

        virtual char const* what() const NO_EXCEPT_VALUE
        {
            return m_message.c_str();
        }

    private:
        const char *PREFIX = "Menu item does not exist: ";
        std::string m_message;
};

#endif // EXCEPTIONS_H_INCLUDED
