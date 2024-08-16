#ifndef INTERPRETER_AST_H_INCLUDED
#define INTERPRETER_AST_H_INCLUDED

#include "command_functions_def.h"
#include <boost/config/warning_disable.hpp>
#include <boost/spirit/home/x3.hpp>
#include <boost/spirit/home/x3/support/ast/variant.hpp>
#include <boost/fusion/include/adapt_struct.hpp>
#include <list>
#include <iostream>

namespace cad::command::interpreter::grammar::calc::ast
{
    namespace x3 = boost::spirit::x3;

    struct nil {};
    struct signed_;
    struct math_expression;
    struct variable;
    struct function_unary;
    struct function_binary;

    struct operand : x3::variant<nil,
        double,
        x3::forward_ast<signed_>,
        x3::forward_ast<math_expression>,
        x3::forward_ast<variable>,
        x3::forward_ast<function_unary>,
        x3::forward_ast<function_binary>>
    {
        using base_type::base_type;
        using base_type::operator=;
    };

    struct signed_
    {
        char sign;
        operand operand_;
    };

    struct operation
    {
        char operator_;
        operand operand_;
    };

    struct math_expression
    {
        operand first;
        std::list<operation> rest;
    };

    struct variable
    {
        std::string name;
    };

    struct function_unary
    {
        lexer_function_unary_pt_t pointer;
        operand arg;
    };

    struct function_binary
    {
        lexer_function_binary_pt_t pointer;
        operand arg_1;
        operand arg_2;
    };

    // TODO REMOVE
    inline std::ostream& operator<<(std::ostream& out, nil)
    {
        out << "nil";
        return out;
    }
}

    BOOST_FUSION_ADAPT_STRUCT(cad::command::interpreter::grammar::calc::ast::signed_, sign, operand_)
    BOOST_FUSION_ADAPT_STRUCT(cad::command::interpreter::grammar::calc::ast::operation, operator_, operand_)
    BOOST_FUSION_ADAPT_STRUCT(cad::command::interpreter::grammar::calc::ast::math_expression, first, rest)
    BOOST_FUSION_ADAPT_STRUCT(cad::command::interpreter::grammar::calc::ast::variable, name)
    BOOST_FUSION_ADAPT_STRUCT(cad::command::interpreter::grammar::calc::ast::function_unary, pointer, arg)
    BOOST_FUSION_ADAPT_STRUCT(cad::command::interpreter::grammar::calc::ast::function_binary, pointer, arg_1, arg_2)

#endif // INTERPRETER_AST_H_INCLUDED
