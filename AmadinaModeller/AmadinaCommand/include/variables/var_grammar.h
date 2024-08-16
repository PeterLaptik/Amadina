#ifndef VAR_GRAMMAR_H_INCLUDED
#define VAR_GRAMMAR_H_INCLUDED

#include "variables/var_ast.h"
#include <boost/spirit/home/x3.hpp>

/// Grammar description for variable assignment expressions.
/// Describes expressions like '{any_characters} = {any_characters}'.
/// Letters, digits and underscore symbols only are allowed for variable names.
namespace cad::command::interpreter::grammar::variables
{
    using boost::spirit::x3::alnum;
    using boost::spirit::x3::char_;
    using cad::command::interpreter::grammar::variables::ast::ExpressionAssign;

    struct ExprVariableAssignment;
    const boost::spirit::x3::rule<ExprVariableAssignment, ExpressionAssign> expression_assign("expression_assign");

    // Grammar rules
    const auto expression_assign_def = (+(alnum | char_('_')) > '=' > +char_);

    BOOST_SPIRIT_DEFINE(expression_assign);

    struct ExprVariableAssignment
    {
        //  Error handler
        template <typename Iterator, typename Exception, typename Context>
        boost::spirit::x3::error_handler_result
        on_error(Iterator&, Iterator const& last, Exception const& x, Context const& context)
        {
            std::cout
                    << "Error! Expecting: "
                    << x.which()
                    << " here: \""
                    << std::string(x.where(), last)
                    << "\""
                    << std::endl;
            return boost::spirit::x3::error_handler_result::fail;
        }
    };

    auto assign_expr = expression_assign;
}

#endif // VAR_GRAMMAR_H_INCLUDED
