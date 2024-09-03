#include "command_line/command_transformer.h"
#include "calculator/calc_grammar.h"
#include "calculator/calc_evaluator.h"
#include "parser_exception.h"

using cad::command::interpreter::CommandToken;
using cad::command::interpreter::grammar::calc::exec::Evaluator;
using cad::command::interpreter::grammar::calc::ast::MathExpression;
using cad::command::interpreter::grammar::calc::expression;
using boost::spirit::x3::ascii::space_type;


const char *const MSG_CALC_ERROR = "Calculation error. ";
const char *const MSG_LIST_ERROR = "Cannot calculate list element. ";


cad::command::interpreter::grammar::commands::ast::CommandTransformer::CommandTransformer(std::map<std::string, double> &vars_list,  std::map<std::string, double> &const_list)
    : m_calc(vars_list, const_list)
{ }

CommandToken cad::command::interpreter::grammar::commands::ast::CommandTransformer::operator()(const Text &token) const
{
    try { // Try consider expression as numeric
        double numeric_value = m_calc.EvaluateMathExpression(token.token);
        return CommandToken(numeric_value);
    }
    catch (const std::exception &e) { // or set as a text
        return CommandToken(token.token, TOKEN_CMD_TEXT);
    }
}

CommandToken cad::command::interpreter::grammar::commands::ast::CommandTransformer::operator()(const String &str) const
{
    return CommandToken(str.value, TOKEN_CMD_STRING);
}

CommandToken cad::command::interpreter::grammar::commands::ast::CommandTransformer::operator()(const List &list) const
{
    std::vector<double> items;
    for (const ListItem &item : list.values)
    {
        try {
            double list_value = m_calc.EvaluateMathExpression(item.value);
            items.push_back(list_value);
        }
        catch (const std::exception &e) {
            std::string msg = MSG_LIST_ERROR;
            msg += ("(" + item.value + ") ");
            msg += e.what();
            throw ParserException(msg);
        }
    }
    return CommandToken(std::move(items));
}