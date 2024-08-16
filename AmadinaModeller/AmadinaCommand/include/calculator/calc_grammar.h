#ifndef INTERPRETER_GRAMMAR_H_INCLUDED
#define INTERPRETER_GRAMMAR_H_INCLUDED

#include "calc_ast.h"
#include "calc_functions.h"
#include <boost/spirit/home/x3.hpp>

namespace cad::command::interpreter::grammar::calc
{
    using boost::spirit::x3::double_;
    using boost::spirit::x3::char_;
    using boost::spirit::x3::alnum;
    using boost::spirit::x3::lexeme;
    using boost::spirit::x3::raw;
    using boost::spirit::x3::alpha;

    unary_function_t u_func;
    binary_function_t b_func;

    struct MathExpressionClass;
    struct term_class;
    struct factor_class;
    struct variable_class;
    struct function_unary_class;
    struct function_binary_class;

    boost::spirit::x3::rule<MathExpressionClass, ast::math_expression> const expression("expression");
    boost::spirit::x3::rule<term_class, ast::math_expression> const term("term");
    boost::spirit::x3::rule<factor_class, ast::operand> const factor("factor");
    boost::spirit::x3::rule<variable_class, ast::variable> const variable("variable");
    boost::spirit::x3::rule<function_binary_class, ast::function_binary> const function_binary("function_binary");
    boost::spirit::x3::rule<function_unary_class, ast::function_unary> const function_unary("function_unary");

    auto const expression_def =
        term >> *(
            (char_('+') > term)
        |   (char_('-') > term)
            );

    auto const term_def =
        factor >> *(
            (char_('*') > factor)
        |   (char_('/') > factor)
            );

    auto const factor_def =
        double_
        | function_unary
        | function_binary
        | variable
        |   '(' > expression > ')'
        |   (char_('-') > factor)
        |   (char_('+') > factor)
        ;

    auto const variable_def =
        '{' > raw[lexeme[alpha >> *(alnum | '_')]] > '}'
        ;

    auto const function_unary_def =
        u_func > '(' > expression > ')'
        ;

    auto const function_binary_def =
        b_func > '(' > expression > ',' > expression > ')'
        ;

    BOOST_SPIRIT_DEFINE(expression, term, factor, variable, function_unary, function_binary);

    struct MathExpressionClass
    {
        //  Our error handler
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

    //auto calculator = expression;
}

#endif // INTERPRETER_GRAMMAR_H_INCLUDED
