#include "command_parser.h"
#include "variables/var_grammar.h"
#include "calculator/calc_grammar.h"
#include "calculator/calc_evaluator.h"
#include <boost/spirit/home/x3.hpp>

// TODO REMOVE
#include <iostream>

const char *MSG_EXECUTED = "OK";
const char *MSG_BAD_VARIABLE_NAME = "Bad variable name. Only letters and underscores are allowed";
const char *MSG_BAD_MATH_EXPRESSION = "Cannot evaluate expression";

bool cad::command::interpreter::CommandParser::ParseCommand(std::string command)
{
    m_result_message.clear();
    if(IsAssignValueExpression(command))
    {
        AssignValue(command);
        return false;
    }

    EvaluateMathExpression(command);
    return true;
}


bool cad::command::interpreter::CommandParser::IsAssignValueExpression(const std::string &command) const
{
    return command.find('=') != std::string::npos;
}

bool cad::command::interpreter::CommandParser::AssignValue(std::string command)
{
    boost::spirit::x3::ascii::space_type space;
    using cad::command::interpreter::grammar::variables::ExpressionAssign;

    auto assign_parser = cad::command::interpreter::grammar::variables::expression_assign;
    auto string_start = command.begin();
    auto string_end = command.end();
    ExpressionAssign expr_result;

    bool res = phrase_parse(string_start, string_end, assign_parser, space, expr_result);
    std::cout << "Result: " << res <<std::endl;
    if(!res)
    {
        m_result_message = MSG_BAD_VARIABLE_NAME;
        return false;
    }

    std::cout << "Assign: " << expr_result.variable << " to " << expr_result.variable_expression << std::endl;

    std::pair<bool,double> numeric_result = EvaluateMathExpression(expr_result.variable_expression);
    if(!numeric_result.first)
    {
        m_result_message = MSG_BAD_MATH_EXPRESSION;
        return false;
    }

    m_variables.insert(std::pair(expr_result.variable, numeric_result.second));

    m_result_message = MSG_EXECUTED;
    return true;
}

std::pair<bool,double> cad::command::interpreter::CommandParser::EvaluateMathExpression(std::string expression)
{

//    using cad::command::interpreter::grammar::math::MathExpressionClass;
    using cad::command::interpreter::grammar::calc::exec::Evaluator;
    using cad::command::interpreter::grammar::calc::ast::math_expression;

    boost::spirit::x3::ascii::space_type space;
    math_expression res;
    auto calc = cad::command::interpreter::grammar::calc::expression;
    auto string_start = expression.begin();
    auto string_end = expression.end();

    Evaluator eval;
    bool r = phrase_parse(string_start, string_end, calc, space, res);
    if(!r)
    {
        std::cout << "Expression error" << calc << "at " << std::string(string_start, string_end) << std::endl;
        return std::pair(false, 0);
    }

    double numeric_result = eval(res);
    std::cout << "Result: " << numeric_result << std::endl;
    return std::pair(true, numeric_result);
}

std::string cad::command::interpreter::CommandParser::GetResultMessage() const
{
    return m_result_message;
}
