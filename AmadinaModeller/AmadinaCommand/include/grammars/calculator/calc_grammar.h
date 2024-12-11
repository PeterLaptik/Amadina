#ifndef CALC_GRAMMAR_H_INCLUDED
#define CALC_GRAMMAR_H_INCLUDED

#include "calc_ast.h"
#include "calc_functions.h"
#include "parser_exception.h"

/// Grammar description for calculator expressions.
/// Describes math expressions.
/// Following operations are allowed: +, -, /, *, brackets, unary and binary functions, variables and constants.
/// Variables and constants should be placed in curly brackets.
/// Example: 1 + cos({PI})*2
namespace cad::command::interpreter::grammar::calc
{
    using boost::spirit::x3::double_;
    using boost::spirit::x3::char_;
    using boost::spirit::x3::alnum;
    using boost::spirit::x3::lexeme;
    using boost::spirit::x3::raw;
    using boost::spirit::x3::alpha;

    static unary_function_t u_func;
    static binary_function_t b_func;

    struct MathExpressionClass;
    struct TermClass;
    struct FactorClass;
    struct VariableClass;
    struct FunctionUnaryClass;
    struct FunctionBinaryClass;

    const boost::spirit::x3::rule<MathExpressionClass, ast::MathExpression> expression("expression");
    const boost::spirit::x3::rule<TermClass, ast::MathExpression> term("term");
    const boost::spirit::x3::rule<FactorClass, ast::Operand> factor("factor");
    const boost::spirit::x3::rule<VariableClass, ast::Variable> variable("variable");
    const boost::spirit::x3::rule<FunctionBinaryClass, ast::FunctionBinary> function_binary("function_binary");
    const boost::spirit::x3::rule<FunctionUnaryClass, ast::FunctionUnary> function_unary("function_unary");


    // Grammar rules
    const auto expression_def =
        term >> *(
            (char_('+') > term)
        |   (char_('-') > term)
            );

    const auto term_def =
        factor >> *(
            (char_('*') > factor)
        |   (char_('/') > factor)
            );

    const auto factor_def =
        double_
        | function_unary
        | function_binary
        | variable
        |   '(' > expression > ')'
        |   (char_('-') > factor)
        |   (char_('+') > factor)
        ;

    const auto variable_def =
        '{' > raw[lexeme[alpha >> *(alnum | '_')]] > '}'
        ;

    const auto function_unary_def =
        u_func > '(' > expression > ')'
        ;

    const auto function_binary_def =
        b_func > '(' > expression > ',' > expression > ')'
        ;


    BOOST_SPIRIT_DEFINE(expression, term, factor, variable, function_unary, function_binary);


    struct MathExpressionClass
    {
        template <typename Iterator, typename Exception, typename Context>
        boost::spirit::x3::error_handler_result
        on_error(Iterator&, Iterator const& last, Exception const& x, Context const& context)
        {
            throw cad::command::interpreter::ParserException("Expecting: " + x.which() +
                " here: \"" + std::string(x.where(), last) + "\"");
        }
    };
}

#endif // CALC_GRAMMAR_H_INCLUDED
