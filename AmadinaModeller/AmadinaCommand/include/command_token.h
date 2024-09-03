#ifndef COMMAND_TOKEN_H_INCLUDED
#define COMMAND_TOKEN_H_INCLUDED

#include <string>
#include <vector>

namespace cad::command::interpreter
{
    enum TokenType
    {
        TOKEN_CMD_TEXT,     // Regular text token
        TOKEN_CMD_NUMERIC,  // Numeric token (double)
        TOKEN_CMD_LIST,     // List of numeric tokens
        TOKEN_CMD_STRING    // Quoted text token
    };

    class CommandToken final
    {
        public:
            CommandToken() = delete;
            explicit CommandToken(const std::string &value, TokenType type);
            explicit CommandToken(std::string &&value, TokenType type);
            explicit CommandToken(double value);
            explicit CommandToken(const std::vector<double> &list);
            explicit CommandToken(std::vector<double> &&list);
            ~CommandToken() = default;

            bool IsText(void) const;
            bool IsNumeric(void) const;
            bool IsList(void) const;
            bool IsString(void) const;

            const std::string& GetStringValue(void) const;
            double GetNumericValue(void) const;
            
            double Get(int i) const;
            bool IsListEmpty() const;
            size_t GetListSize() const;


        private:
            void TextToLower();

            double m_num = 0;
            std::string m_str;
            std::vector<double> m_list;

            TokenType m_type;

            mutable size_t m_list_cursor = 0;
            size_t m_list_size = 0;
    };
}

#endif // COMMAND_TOKEN_H_INCLUDED
