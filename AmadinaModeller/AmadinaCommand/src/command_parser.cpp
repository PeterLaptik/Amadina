#include "command_parser.h"
#include "parser_exception.h"
#include "variables/var_grammar.h"
#include "calculator/calc_grammar.h"
#include "calculator/calc_evaluator.h"

using boost::spirit::x3::ascii::space_type;
using cad::command::interpreter::grammar::variables::expression_assign;
using cad::command::interpreter::grammar::variables::AssignExpression;
using cad::command::interpreter::grammar::calc::exec::Evaluator;
using cad::command::interpreter::grammar::calc::ast::MathExpression;
using cad::command::interpreter::grammar::calc::expression;
using cad::command::interpreter::CommandParser;

const char * const MSG_EXECUTED = "OK";
const char * const MSG_CONSTANT_OVERRIDING = "Cannot override constant value: ";
const char * const MSG_ASSIGN_ERROR = "Assignment error. Check variable name.";
const char * const MSG_CALC_ERROR = "Calculation error.";

bool cad::command::interpreter::CommandParser::ParseCommand(const std::string &command)
{
    m_result_message = MSG_EXECUTED;

    if (IsAssignValueExpression(command))
        return AssignValue(command);

    double res = EvaluateMathExpression(command);

    return true;
}


bool cad::command::interpreter::CommandParser::IsAssignValueExpression(const std::string &command) const
{
    return command.find('=') != std::string::npos;
}

bool cad::command::interpreter::CommandParser::AssignValue(const std::string &command)
{
    try {
        EvaluateAssignmentExpression(command);
    } catch (const ParserException &e) {
        m_result_message = e.what();
        return false;
    }
    return true;
}

void cad::command::interpreter::CommandParser::EvaluateAssignmentExpression(const std::string &a_expr)
{
    space_type space;
    auto assign_parser = expression_assign;
    AssignExpression expr_result;

    auto string_start = a_expr.begin();
    auto string_end = a_expr.end();

    bool res = phrase_parse(string_start, string_end, assign_parser, space, expr_result);

    if (!res)
        throw ParserException(MSG_ASSIGN_ERROR);

    double numeric_result = EvaluateMathExpression(expr_result.variable_expression);
    PutVariable(expr_result.variable, numeric_result);
}

double cad::command::interpreter::CommandParser::EvaluateMathExpression(const std::string &math_expr)
{
    space_type space;
    auto calc = expression;
    Evaluator eval(m_variables, m_constants);
    MathExpression result_ast;

    auto string_start = math_expr.begin();
    auto string_end = math_expr.end();

    bool res = phrase_parse(string_start, string_end, calc, space, result_ast);

    if (!res)
        throw ParserException(MSG_CALC_ERROR);

    return eval(result_ast);
}

void cad::command::interpreter::CommandParser::PutVariable(const std::string &var_name, double var_value)
{
    if(DoesConstantExist(var_name))
        throw ParserException(MSG_CONSTANT_OVERRIDING + var_name);

    m_variables[var_name] = var_value;
}

void cad::command::interpreter::CommandParser::PutConstant(const std::string &const_name, double const_value)
{
    auto [it, result] = m_constants.insert(std::make_pair(const_name, const_value));
    if(!result)
        throw ParserException(MSG_CONSTANT_OVERRIDING + const_name);
}

bool cad::command::interpreter::CommandParser::DoesConstantExist(const std::string &constant_name) const
{
    return m_constants.find(constant_name) != m_constants.end();
}

std::string cad::command::interpreter::CommandParser::GetResultMessage() const
{
    return m_result_message;
}
