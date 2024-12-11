#ifndef COMMAND_AST_H_INCLUDED
#define COMMAND_AST_H_INCLUDED

#include "command_token.h"
#include <boost/spirit/home/x3.hpp>
#include <boost/spirit/home/x3/support/ast/variant.hpp>
#include <boost/fusion/include/adapt_struct.hpp>
#include <string>

namespace cad::command::interpreter::grammar::commands::ast
{
    namespace x3 = boost::spirit::x3;

    struct Text
    {
        std::string token;
    };

    struct String
    {
        std::string value;
    };

    struct ListItem
    {
        std::string value;
    };

    struct List
    {
        std::vector<ListItem> values;
    };

    struct Token : x3::variant<Text, String, List>
    {
        using base_type::base_type;
        using base_type::operator=;
    };

    struct TokenList
    {
        std::vector<Token> tokens;
    };

    class VisitorTransformer
    {
        public:
            TokenType operator()(const Text &token) const
            {
                return TOKEN_CMD_TEXT;
            }

            TokenType operator()(const String &str) const
            {
                return TOKEN_CMD_STRING;
            }

            TokenType operator()(const List &list) const
            {
                return TOKEN_CMD_LIST;
            }

        
    };

    class VisitorDebug
    {
        public:
            std::string operator()(const Text &token) const
            {
                return "Token:" + token.token;
            }

            std::string operator()(const String &str) const
            {
                return "String:" + str.value;
            }

            std::string operator()(const List &list) const
            {
                std::string result = "List: [";
                for (auto val : list.values)
                {
                    result += val.value;
                    result += ',';
                }
                result += "]";
                result += "(size " + std::to_string(list.values.size()) + ')';
                return result;
            }
    };
}

BOOST_FUSION_ADAPT_STRUCT(cad::command::interpreter::grammar::commands::ast::Text, token)
BOOST_FUSION_ADAPT_STRUCT(cad::command::interpreter::grammar::commands::ast::TokenList, tokens)
BOOST_FUSION_ADAPT_STRUCT(cad::command::interpreter::grammar::commands::ast::String, value)
BOOST_FUSION_ADAPT_STRUCT(cad::command::interpreter::grammar::commands::ast::List, values)
BOOST_FUSION_ADAPT_STRUCT(cad::command::interpreter::grammar::commands::ast::ListItem, value)

#endif // !COMMAND_AST_H_INCLUDED

