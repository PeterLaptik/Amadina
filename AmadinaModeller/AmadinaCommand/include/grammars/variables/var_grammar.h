#ifndef VAR_GRAMMAR_H_INCLUDED
#define VAR_GRAMMAR_H_INCLUDED

#include "grammars/variables/var_ast.h"
#include "parser_exception.h"
#include <boost/spirit/home/x3.hpp>

/// Grammar description for variable assignment expressions.
/// Describes expressions like '{any_characters} = {any_characters}'.
/// Letters, digits and underscore symbols only are allowed for variable names.
namespace cad::command::interpreter::grammar::variables
{
    using boost::spirit::x3::alnum;
    using boost::spirit::x3::char_;
    using cad::command::interpreter::grammar::variables::ast::AssignExpression;

    struct ExprVariableAssignment;
    const boost::spirit::x3::rule<ExprVariableAssignment, AssignExpression> expression_assign("expression_assign");

    // Grammar rules
    const auto expression_assign_def = (+(alnum | char_('_')) > '=' > +char_);

    BOOST_SPIRIT_DEFINE(expression_assign);

    struct ExprVariableAssignment
    {
        template <typename Iterator, typename Exception, typename Context>
        boost::spirit::x3::error_handler_result
        on_error(Iterator&, const Iterator &last, const Exception &x, const Context &context)
        {
            throw cad::command::interpreter::ParserException("Bad variable name. Only letters and underscores are allowed.");
        }
    };
}

#endif // VAR_GRAMMAR_H_INCLUDED
