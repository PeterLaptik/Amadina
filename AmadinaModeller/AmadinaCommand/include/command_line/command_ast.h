#ifndef COMMAND_AST_H_INCLUDED
#define COMMAND_AST_H_INCLUDED

#include <boost/fusion/include/adapt_struct.hpp>
#include <string>

namespace cad::command::interpreter::grammar::commands::ast
{
    namespace x3 = boost::spirit::x3;

    struct CommandTokenExpr
    {
        std::string token;
    };

    struct CommandString
    {
        std::string value;
    };

    struct ListElement
    {
        std::string value;
    };

    struct List
    {
        std::vector<ListElement> values;
    };

    struct Token : x3::variant<CommandTokenExpr, CommandString, List>
    {
        using base_type::base_type;
        using base_type::operator=;
    };

    struct CommandTokenListExpr
    {
        std::vector<Token> values;
    };

    class Visitor
    {
        public:

            std::string operator()(const std::string &str) const
            {
                return str;
            }

            std::string operator()(const CommandTokenExpr &token) const
            {
                return "Token:" + token.token;
            }

            std::string operator()(const CommandString &str) const
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
                return result;
            }
    };
}

BOOST_FUSION_ADAPT_STRUCT(cad::command::interpreter::grammar::commands::ast::CommandTokenExpr, token)
BOOST_FUSION_ADAPT_STRUCT(cad::command::interpreter::grammar::commands::ast::CommandTokenListExpr, values)
BOOST_FUSION_ADAPT_STRUCT(cad::command::interpreter::grammar::commands::ast::CommandString, value)
BOOST_FUSION_ADAPT_STRUCT(cad::command::interpreter::grammar::commands::ast::List, values)
BOOST_FUSION_ADAPT_STRUCT(cad::command::interpreter::grammar::commands::ast::ListElement, value)

#endif // !COMMAND_AST_H_INCLUDED

