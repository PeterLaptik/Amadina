#include "calculator/calc_evaluator.h"
#include "parser_exception.h"
#include <numeric>

const char *const MSG_DIVIDING_BY_ZERO = "Dividing by zero. ";
const char *const MSG_UNKNOWN_VARIABLE = "Unknown variable. ";
const char *const MSG_BAD_PTR = "Bad pointer for function. ";
const char *const MSG_BAD_OPER_BINARY = "Unknown binary operation. ";
const char *const MSG_BAD_OPER_UNARY = "Unknown unary operation. ";

cad::command::interpreter::grammar::calc::exec::Evaluator::Evaluator(std::map<std::string, double> &vars_list,
    std::map<std::string, double> &const_list)
    : m_variables(vars_list), m_constants(const_list)
{ }

double cad::command::interpreter::grammar::calc::exec::Evaluator::operator()(double n) const
{
    return n;
}

double cad::command::interpreter::grammar::calc::exec::Evaluator::operator()(double lhs, Operation const &x) const
{
    double rhs = boost::apply_visitor(*this, x.operand);
    switch (x.operator_ch)
    {
        case '+':
            return lhs + rhs;
        case '-':
            return lhs - rhs;
        case '*':
            return lhs * rhs;
        case '/':
            if(fabs(rhs) < (std::numeric_limits<double>::epsilon()))
                throw ParserException(MSG_DIVIDING_BY_ZERO + std::to_string(lhs)
                    + " / " + std::to_string(rhs));
            return lhs / rhs;
    }

    throw ParserException(MSG_BAD_OPER_BINARY + '(' + x.operator_ch + ')');
    return 0;
}

double cad::command::interpreter::grammar::calc::exec::Evaluator::operator()(const Variable &var) const
{
    double result = 0;
    auto var_value = m_variables.find(var.name);
    if (var_value != m_variables.end())
        return var_value->second;

    auto const_value = m_constants.find(var.name);
        if (const_value != m_constants.end())
            return const_value->second;

        throw ParserException(MSG_UNKNOWN_VARIABLE + '{' + var.name + '}');
}

double cad::command::interpreter::grammar::calc::exec::Evaluator::operator()(const FunctionUnary &fn) const
{
    double rhs = boost::apply_visitor(*this, fn.arg);
    if(!fn.pointer)
        throw ParserException(MSG_BAD_PTR);

    return fn.pointer(rhs);
}

double cad::command::interpreter::grammar::calc::exec::Evaluator::operator()(const FunctionBinary &fn) const
{
    double lhs = boost::apply_visitor(*this, fn.arg_1);
    double rhs = boost::apply_visitor(*this, fn.arg_2);
    if (!fn.pointer)
        throw ParserException(MSG_BAD_PTR);

    return fn.pointer(lhs, rhs);
}

double cad::command::interpreter::grammar::calc::exec::Evaluator::operator()(const Signed &x) const
{
    double rhs = boost::apply_visitor(*this, x.operand);
    switch (x.sign)
    {
        case '-':
            return -rhs;
        case '+':
            return +rhs;
        }
    throw ParserException(MSG_BAD_OPER_BINARY + '(' + x.sign + ')');
    return 0;
}

double cad::command::interpreter::grammar::calc::exec::Evaluator::operator()(const MathExpression &x) const
{
    return std::accumulate(x.rest.begin(), x.rest.end(),
        boost::apply_visitor(*this, x.first),
        *this);
}
