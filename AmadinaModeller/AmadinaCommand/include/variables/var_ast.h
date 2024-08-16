#ifndef VAR_AST_H_INCLUDED
#define VAR_AST_H_INCLUDED

#include <boost/fusion/include/adapt_struct.hpp>

namespace cad::command::interpreter::grammar::variables::ast
{
    struct ExpressionAssign
    {
        std::string variable;               // variable name
        std::string variable_expression;    // right-hand expression
    };
}

BOOST_FUSION_ADAPT_STRUCT(cad::command::interpreter::grammar::variables::ast::ExpressionAssign, variable, variable_expression)

#endif // VAR_AST_H_INCLUDED
