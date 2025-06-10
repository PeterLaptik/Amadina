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
        TOKEN_CMD_STRING,   // Quoted text token
        TOKEN_NULL          // Empty token
    };

    class CommandToken final
    {
        public:
            explicit CommandToken();
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
            bool IsNull(void) const;

            const std::string& GetStringValue(void) const;
            double GetNumericValue(void) const;
            
            double GetListValue(size_t i) const;
            bool IsListEmpty() const;
            size_t GetListSize() const;


        private:
            void TextToLower();

            double m_num = 0;
            std::string m_str = "";
            std::vector<double> m_list;

            TokenType m_type;
    };
}

#endif // COMMAND_TOKEN_H_INCLUDED
