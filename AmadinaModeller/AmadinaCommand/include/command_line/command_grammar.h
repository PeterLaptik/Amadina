#ifndef COMMAND_GRAMMAR_H_INCLUDED
#define COMMAND_GRAMMAR_H_INCLUDED

#include "command_ast.h"
#include <boost/spirit/home/x3.hpp>
#include <iostream>

namespace cad::command::interpreter::grammar::commands
{
    using boost::spirit::x3::alnum;
    using boost::spirit::x3::char_;
    using boost::spirit::x3::graph;
    using boost::spirit::x3::lexeme;
    using cad::command::interpreter::grammar::variables::ast::AssignExpression;

    struct ExprCommands;
    struct ExprCommandList;
    struct ExprString;
    struct ExprValue;
    struct ExprList;
    struct ExprListElement;
    const boost::spirit::x3::rule<ExprCommandList, ast::CommandTokenListExpr> command_token_list("command_token_list");
    const boost::spirit::x3::rule<ExprCommands, ast::CommandTokenExpr> command_token("command_token");
    const boost::spirit::x3::rule<ExprString, ast::CommandString> command_string("command_string");
    const boost::spirit::x3::rule<ExprValue, ast::Token> value("value");
    const boost::spirit::x3::rule<ExprList, ast::List> command_list("command_list");
    const boost::spirit::x3::rule<ExprListElement, ast::ListElement> list_element("list_element");

    // Grammar rules
    const auto command_token_def = lexeme[+(graph - '"' - '[' - ']')];

    const auto list_element_def = lexeme[+(char_ - '"' - '[' - ']')];

    const auto command_string_def = lexeme['"' >> +(graph - '"') >> '"'];

    const auto command_list_def = lexeme['[' >> (list_element % ',') >> ']'];

    const auto value_def = command_token | command_string | command_list;

    const auto command_token_list_def = (value % ' ');

    BOOST_SPIRIT_DEFINE(command_token_list, command_token, command_string, command_list, value, list_element);

    struct ExprCommands
    {
        template <typename Iterator, typename Exception, typename Context>
        boost::spirit::x3::error_handler_result
            on_error(Iterator &, const Iterator &last, const Exception &x, const Context &context)
        {
            std::cout
                << "Error! Expecting: "
                << x.which()
                << " here: \""
                << std::string(x.where(), last)
                << "\""
                << std::endl
                ;
            return boost::spirit::x3::error_handler_result::fail;
        }
    };
}

#endif // !COMMAND_GRAMMAR_H_INCLUDED

