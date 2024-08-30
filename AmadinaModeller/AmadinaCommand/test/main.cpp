//#define BOOST_TEST_MODULE test module name
//#include <boost/test/included/unit_test.hpp>

//#include "command_parser.h"
#include "parser_exception.h"
//#include "command_functions_def.h"
#include "variables/var_grammar.h"
#include "calculator/calc_grammar.h"
#include "calculator/calc_evaluator.h"
#include "command_line/command_grammar.h"
#include "assert.h"
#include <boost/spirit/home/x3.hpp>
#include <iostream>

void check_math_calcultions(void);
void check_command_line_expressions(void);
bool equal(double first, double second);

const double ALLOWABLE_MARGIN_IN_PERCENT = 1;



int main()
{
    try {
        //check_math_calcultions();
    } catch (const std::exception &e) {
        std::cout << std::endl << "Error: " << e.what() << std::endl;
        return 1;
    }
    
    try {
        check_command_line_expressions();
    }
    catch (const std::exception &e) {
        std::cout << std::endl << "Error: " << e.what() << std::endl;
        return 1;
    }
    

    return 0;
}

void check_command_line_expressions(void)
{
    using boost::spirit::x3::ascii::space_type;
    using boost::spirit::x3::ascii::blank_type;
    //using cad::command::interpreter::grammar::commands::command_token;
    using cad::command::interpreter::grammar::commands::command_token_list;
   //using cad::command::interpreter::grammar::commands::ast::CommandTokenExpr;
    using cad::command::interpreter::grammar::commands::ast::CommandTokenListExpr;
    using cad::command::interpreter::grammar::commands::ast::Visitor;

    //CommandTokenExpr command_token_expr;
    CommandTokenListExpr command_token_expr;

    space_type space;
    blank_type blank;
    std::string expr = "123 aaa \"test\" xx \"z\" xxx [abc, 101, 1c + 5] ccc";

    auto cmd_parser = command_token_list;
    //auto cmd_parser = command_token;

    auto string_start = expr.begin();
    auto string_end = expr.end();

    bool ares = phrase_parse(string_start, string_end, cmd_parser, "\t", command_token_expr);
    if(!ares)
        std::cout << "Error!!!" << std::endl;

    Visitor vis;
    std::cout << "Values:" << std::endl;
    for (auto &val : command_token_expr.values)
    {
        std::cout << boost::apply_visitor(vis, val) << std::endl;
    }

    if (string_start != string_end)
    {
        std::cout << "Tail: " << std::string(string_start, string_end) << " -> " << ares << std::endl;
    }
    //std::cout << "Result: " << command_token_expr.values << " -> " << std::endl;
}

const std::vector<std::pair<std::string, double>> math_expressions = {
    {"b = 10", 10},
    {"20 + {b}", 30},
    {"sin({PI}/2)", 1},
    {"pow(2,2)*2.5*(5+5)", 100},
    {"pow(sin({PI}/4),2)+pow(cos({PI}/4),2)", 1},
    {"2.5*4/(1.5*2)", 3.33},
    {"rad(90)", 3.14/2},
    {"deg(3.14/4)", 45},
    {"abs(-5) + acos(0)", 6.57},
    {"abs(-5) + asin(1)", 6.57},
    {"cosh(1)/((exp(1) + exp(-1))/2)", 1},
    {"deg(atan(1))", 45},
    {"log(exp(2))+log10(pow(10,2))", 4},
    {"sqrt(pow(0.28, 2))", 0.28},
    {"tan(rad(45))", 1},
    {"sinh(1)+tanh(1)", 1.937},
    {"b=20", 20},
    {"{b}", 20}
};

void check_math_calcultions()
{
    using boost::spirit::x3::ascii::space_type;
    using cad::command::interpreter::grammar::variables::expression_assign;
    using cad::command::interpreter::grammar::variables::AssignExpression;
    using cad::command::interpreter::grammar::calc::exec::Evaluator;
    using cad::command::interpreter::grammar::calc::ast::MathExpression;
    using cad::command::interpreter::grammar::calc::expression;

    std::map<std::string, double> local_variables;
    std::map<std::string, double> constants = {
        {"PI", 3.14}
    };

    space_type space;
    auto assign_parser = expression_assign;

    auto calc = expression;
    Evaluator eval(local_variables, constants);

    std::cout << "Math expressions test: " << std::endl;
    for (auto &[expr, value] : math_expressions)
    {
        AssignExpression expr_result;
        MathExpression result_ast;

        std::cout << "Parsing: '" << expr << "'\tExpected value: ";
        if (expr.find('=') != std::string::npos) // Assignment, if the expression contains '=' character
        {
            std::cout << "assignment";

            auto string_start = expr.begin();
            auto string_end = expr.end();

            bool ares = phrase_parse(string_start, string_end, assign_parser, space, expr_result);
            if (!ares)
                assert(0);

            auto math_expr_start = expr_result.variable_expression.begin();
            auto math_expr_end = expr_result.variable_expression.end();

            phrase_parse(math_expr_start, math_expr_end, calc, space, result_ast);

            double result = eval(result_ast);
            local_variables[expr_result.variable] = result;

            std::cout << "\tassigned: " << result << " to '" << expr_result.variable << "'\tOK" << std::endl;
        }
        else // Direct calculation
        {
            auto string_start = expr.begin();
            auto string_end = expr.end();

            bool ares = phrase_parse(string_start, string_end, calc, space, result_ast);
            if (!ares)
                assert(0);

            double result = eval(result_ast);
            bool check_result = equal(result, value);

            std::cout << value << "\t\tComputed value: " << result << "\t" << (check_result ? "OK" : "NOT PASSED") << std::endl;
            assert(check_result);
        }
    }
}

bool equal(double first, double second)
{
    return std::fabs(first - second) / second * 100 <= ALLOWABLE_MARGIN_IN_PERCENT;
}