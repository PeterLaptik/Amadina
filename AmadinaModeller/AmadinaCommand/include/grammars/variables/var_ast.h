#ifndef VAR_AST_H_INCLUDED
#define VAR_AST_H_INCLUDED

#include <string>
#include <boost/fusion/include/adapt_struct.hpp>

namespace cad::command::interpreter::grammar::variables::ast
{
    struct AssignExpression
    {
        std::string variable;               // variable name
        std::string variable_expression;    // right-hand expression
    };
}

BOOST_FUSION_ADAPT_STRUCT(cad::command::interpreter::grammar::variables::ast::AssignExpression, variable, variable_expression)

#endif // VAR_AST_H_INCLUDED
