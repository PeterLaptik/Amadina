#include "command_parser.h"
#include "parser_exception.h"
#include "grammars/variables/var_assigner.h"
#include "grammars/command_line/command_grammar.h"
#include "grammars/command_line/command_transformer.h"
#include "grammars/variables/var_grammar.h"
#include "grammars/calculator/calc_grammar.h"
#include "grammars/calculator/calc_evaluator.h"
#include <boost/spirit/home/x3/support/ast/variant.hpp>

using boost::spirit::x3::ascii::space_type;

using cad::command::interpreter::CommandParser;
using cad::command::interpreter::CommandToken;
using cad::command::interpreter::CommandArguments;
using cad::command::interpreter::grammar::variables::expression_assign;
using cad::command::interpreter::grammar::variables::AssignExpression;
using cad::command::interpreter::grammar::calc::exec::Evaluator;
using cad::command::interpreter::grammar::calc::ast::MathExpression;
using cad::command::interpreter::grammar::calc::expression;
using cad::command::interpreter::grammar::commands::ast::CommandTransformer;

using cad::command::interpreter::grammar::commands::ast::Token;
using cad::command::interpreter::grammar::commands::ast::Text;
using cad::command::interpreter::grammar::commands::ast::String;
using cad::command::interpreter::grammar::commands::ast::List;
using cad::command::interpreter::grammar::commands::ast::ListItem;

using cad::command::interpreter::grammar::variables::VarAssigner;

const char * const MSG_EXECUTED = "OK";
const char * const MSG_CONSTANT_OVERRIDING = "Cannot override constant value. ";
const char * const MSG_ASSIGN_ERROR = "Assignment error. Check variable name. ";
const char * const MSG_CALC_ERROR = "Calculation error. ";
const char * const MSG_CMD_ERROR = "Command read error. ";

bool cad::command::interpreter::CommandParser::ParseCommand(const std::string &command)
{
    m_tokens.clear();
    m_result_message = MSG_EXECUTED;

    if (IsAssignValueExpression(command))
    {
        bool assignment_result = AssignValue(command);
        return assignment_result;
    }
    
    bool parsing_result = TokenizeCommandLine(command);
    return parsing_result;
}

bool cad::command::interpreter::CommandParser::IsEmpty() const
{
    return m_tokens.empty();
}

std::string cad::command::interpreter::CommandParser::GetCommand() const
{
    return !m_tokens.empty() ? m_tokens[0].GetStringValue() : "";
}

CommandArguments cad::command::interpreter::CommandParser::GetArguments() const
{
    return CommandArguments(m_tokens);
}

bool cad::command::interpreter::CommandParser::TokenizeCommandLine(const std::string &command)
{
    using boost::spirit::x3::ascii::char_;
    using cad::command::interpreter::grammar::commands::token_list;
    using cad::command::interpreter::grammar::commands::ast::TokenList;
    using cad::command::interpreter::grammar::commands::ast::VisitorTransformer;

    std::string expression = Normalize(command);

    TokenList command_token_expr;
    auto cmd_parser = token_list;

    auto string_start = expression.begin();
    auto string_end = expression.end();

    bool parse_res = phrase_parse(string_start, string_end, cmd_parser, char_('\\'), command_token_expr);

    // Result is OK + full expression was parsed
    bool cmd_res = parse_res && (string_start == string_end);
    if (!cmd_res)
    {
        std::string details = (string_start == string_end) ? 
            "" 
            : '\'' + std::string(string_start, string_end) + '\'';
        m_result_message = MSG_CMD_ERROR +  details;
        return false;
    }

    // Process tokens
    CommandTransformer visitor(m_variables, m_constants);
    for (auto &token : command_token_expr.tokens)
    {
        m_tokens.push_back(boost::apply_visitor(visitor, token));
    }

    return true;
}


bool cad::command::interpreter::CommandParser::IsAssignValueExpression(const std::string &command) const
{
    return command.find('=') != std::string::npos;
}

std::string cad::command::interpreter::CommandParser::Normalize(const std::string &command) const
{
    // Remove multiply spaces
    std::string result = command;
    auto pos = result.find("  ");
    while (pos != std::string::npos)
    {
        result.replace(pos, 2, " ");
        pos = result.find("  ");
    }
    // Left trim
    size_t lpos = result.find_first_not_of(' ');
    result.erase(0, lpos);
    // Right trim
    size_t rpos = result.find_last_not_of(' ');
    result.erase(rpos + 1);
    return result;
}

bool cad::command::interpreter::CommandParser::AssignValue(const std::string &command)
{
    VarAssigner assigner(m_variables, m_constants);
    try {
        assigner.AssignVar(command);
    } catch (const ParserException &e) {
        m_result_message = e.what();
        return false;
    }
    return true;
}

std::string cad::command::interpreter::CommandParser::GetResultMessage() const
{
    return m_result_message;
}