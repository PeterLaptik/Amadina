#include "grammars/calculator/base_calculator.h"
#include "grammars/calculator/calc_grammar.h"
#include "grammars/calculator/calc_evaluator.h"
#include "parser_exception.h"

using cad::command::interpreter::grammar::calc::exec::Evaluator;
using cad::command::interpreter::grammar::calc::ast::MathExpression;
using cad::command::interpreter::grammar::calc::expression;
using boost::spirit::x3::ascii::space_type;


const char *const MSG_CALC_ERROR = "Calculation error. ";


cad::command::interpreter::grammar::calc::BaseCalculator::BaseCalculator(std::map<std::string, double> &vars_list, std::map<std::string, double> &const_list)
    : m_variables(vars_list), m_constants(const_list)
{ }

double cad::command::interpreter::grammar::calc::BaseCalculator::EvaluateMathExpression(const std::string & math_expr) const
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

    if (string_start != string_end)
    {
        std::string msg = MSG_CALC_ERROR;
        msg += ("'" + std::string(string_start, string_end) + "'");
        throw ParserException(msg);
    }

    return eval(result_ast);
}
