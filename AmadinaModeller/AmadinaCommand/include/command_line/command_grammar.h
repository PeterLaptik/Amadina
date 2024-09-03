#ifndef COMMAND_GRAMMAR_H_INCLUDED
#define COMMAND_GRAMMAR_H_INCLUDED

#include "command_ast.h"
#include <iostream>

/// Grammar description for command line expressions.
/// Describes lexicographical tokens delimited by spaces.
/// For example:
/// my_command abc "xyz" [1,2,3]
/// here:
/// my_command - text token
/// abc - text token
/// "xyz" - string token
/// [1,2,3] - list token (contains three numeric values: 1,2,3)
namespace cad::command::interpreter::grammar::commands
{
    using boost::spirit::x3::alnum;
    using boost::spirit::x3::char_;
    using boost::spirit::x3::graph;
    using boost::spirit::x3::lexeme;

    struct TextExpr;
    struct TokenListExpr;
    struct StringExpr;
    struct TokenExpr;
    struct ListExpr;
    struct ListItemExpr;

    const boost::spirit::x3::rule<TokenListExpr, ast::TokenList> token_list("token_list");
    const boost::spirit::x3::rule<TextExpr, ast::Text> text("text");
    const boost::spirit::x3::rule<StringExpr, ast::String> string("string");
    const boost::spirit::x3::rule<TokenExpr, ast::Token> token("token");
    const boost::spirit::x3::rule<ListExpr, ast::List> list("list");
    const boost::spirit::x3::rule<ListItemExpr, ast::ListItem> list_item("list_item");


    // Grammar rules
    const auto text_def = lexeme[+(graph - '"' - '[' - ']')]; // Regular text

    const auto list_item_def = lexeme[+(char_ - "," - '"' - '[' - ']')];

    const auto string_def = lexeme['"' >> +(graph - '"') >> '"']; // Quoted text

    const auto list_def = ('[' >> (list_item % ',') >> ']');

    const auto token_def = text | string | list;

    const auto token_list_def = (token % ' ');


    BOOST_SPIRIT_DEFINE(token_list, text, string, list, token, list_item);


    struct TextExpr
    {
        template <typename Iterator, typename Exception, typename Context>
        boost::spirit::x3::error_handler_result
            on_error(Iterator &, const Iterator &last, const Exception &x, const Context &context)
        {
            throw ParserException("Expecting: " + x.which() +
                " here: \"" + std::string(x.where(), last) + "\"");
        }
    };
}

#endif // !COMMAND_GRAMMAR_H_INCLUDED

