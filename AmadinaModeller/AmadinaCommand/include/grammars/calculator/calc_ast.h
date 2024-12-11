#ifndef INTERPRETER_AST_H_INCLUDED
#define INTERPRETER_AST_H_INCLUDED

#include "command_functions_def.h"
#include <boost/spirit/home/x3/support/ast/variant.hpp>
#include <boost/fusion/include/adapt_struct.hpp>
#include <vector>

namespace cad::command::interpreter::grammar::calc::ast
{
    namespace x3 = boost::spirit::x3;

    struct Signed;
    struct MathExpression;
    struct Variable;
    struct FunctionUnary;
    struct FunctionBinary;

    struct Operand : x3::variant<double,
        x3::forward_ast<Signed>,
        x3::forward_ast<MathExpression>,
        x3::forward_ast<Variable>,
        x3::forward_ast<FunctionUnary>,
        x3::forward_ast<FunctionBinary>>
    {
        using base_type::base_type;
        using base_type::operator=;
    };

    struct Signed
    {
        char sign;
        Operand operand;
    };

    struct Operation
    {
        char operator_ch;
        Operand operand;
    };

    struct MathExpression
    {
        Operand first;
        std::vector<Operation> rest;
    };

    struct Variable
    {
        std::string name;
    };

    struct FunctionUnary
    {
        lexer_function_unary_pt_t pointer;
        Operand arg;
    };

    struct FunctionBinary
    {
        lexer_function_binary_pt_t pointer;
        Operand arg_1;
        Operand arg_2;
    };
}

    BOOST_FUSION_ADAPT_STRUCT(cad::command::interpreter::grammar::calc::ast::Signed, sign, operand)
    BOOST_FUSION_ADAPT_STRUCT(cad::command::interpreter::grammar::calc::ast::Operation, operator_ch, operand)
    BOOST_FUSION_ADAPT_STRUCT(cad::command::interpreter::grammar::calc::ast::MathExpression, first, rest)
    BOOST_FUSION_ADAPT_STRUCT(cad::command::interpreter::grammar::calc::ast::Variable, name)
    BOOST_FUSION_ADAPT_STRUCT(cad::command::interpreter::grammar::calc::ast::FunctionUnary, pointer, arg)
    BOOST_FUSION_ADAPT_STRUCT(cad::command::interpreter::grammar::calc::ast::FunctionBinary, pointer, arg_1, arg_2)

#endif // INTERPRETER_AST_H_INCLUDED
