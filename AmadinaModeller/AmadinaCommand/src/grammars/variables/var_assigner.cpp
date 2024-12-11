#include "grammars/variables/var_assigner.h"
#include "grammars/variables/var_grammar.h"
#include "parser_exception.h"
#include <boost/spirit/home/x3.hpp>

using boost::spirit::x3::ascii::space_type;
using cad::command::interpreter::grammar::variables::expression_assign;
using cad::command::interpreter::grammar::variables::AssignExpression;


const char *const MSG_ASSIGN_ERROR = "Assignment error. Check variable name. ";
const char *const MSG_CONSTANT_OVERRIDING = "Cannot override constant value. ";


cad::command::interpreter::grammar::variables::VarAssigner::VarAssigner(std::map<std::string, double> &vars_list, std::map<std::string, double> &const_list)
    : m_calc(vars_list, const_list), 
    m_variables(vars_list), m_constants(const_list)
    
{ }

void cad::command::interpreter::grammar::variables::VarAssigner::AssignVar(std::string expression)
{
    space_type space;
    auto assign_parser = expression_assign;
    AssignExpression expr_result; // variable name + right hand expression

    auto string_start = expression.begin();
    auto string_end = expression.end();

    bool res = phrase_parse(string_start, string_end, assign_parser, space, expr_result);

    if (!res)
        throw ParserException(MSG_ASSIGN_ERROR);

    double numeric_result = m_calc.EvaluateMathExpression(expr_result.variable_expression);
    PutVariable(expr_result.variable, numeric_result);
}

void cad::command::interpreter::grammar::variables::VarAssigner::PutVariable(const std::string &var_name, double var_value) const
{
    if (DoesConstantExist(var_name))
        throw ParserException(MSG_CONSTANT_OVERRIDING + '{' + var_name + '}');

    m_variables[var_name] = var_value;
}

void cad::command::interpreter::grammar::variables::VarAssigner::PutConstant(const std::string &const_name, double const_value) const
{
    auto [it, result] = m_constants.insert(std::make_pair(const_name, const_value));
    if (!result)
        throw ParserException(MSG_CONSTANT_OVERRIDING + '{' + const_name + '}');
}

bool cad::command::interpreter::grammar::variables::VarAssigner::DoesConstantExist(const std::string &constant_name) const
{
    return m_constants.find(constant_name) != m_constants.end();
}
