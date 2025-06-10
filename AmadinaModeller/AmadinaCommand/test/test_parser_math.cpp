#include "command_parser.h"
#include "parser_exception.h"
#include "grammars/variables/var_assigner.h"
#include "grammars/calculator/base_calculator.h"
#include "grammars/variables/var_grammar.h"
#include "grammars/calculator/calc_grammar.h"
#include "grammars/calculator/calc_evaluator.h"
#include "grammars/command_line/command_grammar.h"
#include <boost/spirit/home/x3.hpp>
#include <assert.h>
#include <iostream>

using cad::command::interpreter::grammar::variables::VarAssigner;
using cad::command::interpreter::grammar::calc::BaseCalculator;

// Epsilon for double numbers comparation
const double ALLOWABLE_MARGIN_IN_PERCENT = 1;

// Floating point numbers comparator
bool equal(double first, double second);

// Good math expressions including assignments,
// have to pass with no errors.
// Expression -> expecting value
const std::vector<std::pair<std::string, double>> math_expressions = {
    {"b = 10", 10},
    {"20 + {b}", 30},
    {"sin({PI}/2)", 1},
    {"pow(2,2)*2.5*(5+5)", 100},
    {"pow(sin({PI}/4),2)+pow(cos({PI}/4),2)", 1},
    {"2.5*4/(1.5*2)", 3.33},
    {"rad(90)", 3.14 / 2},
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
    {"{b}", 20},
    {"a_2 = 50", 50}
};

void check_math_calcultions()
{
    std::map<std::string, double> local_variables;
    std::map<std::string, double> constants = {
        {"PI", 3.14}
    };

    std::cout << "Math expressions evaluation test: " << std::endl;

    // Calculate all expressions with output results
    for (auto &[expr, value] : math_expressions)
    {
        VarAssigner var_assigner(local_variables, constants);
        BaseCalculator base_calc(local_variables, constants);

        std::cout << "Parsing: '" << expr << "'";

        if (expr.find('=') != std::string::npos) // Assignment, if the expression contains '=' character
        {
            std::cout << "\tassignment";
            var_assigner.AssignVar(expr);
            std::cout << "\tassigned: " << "OK" << std::endl;
        }
        else // Direct calculation
        {
            double result = base_calc.EvaluateMathExpression(expr);
            bool check_result = equal(result, value);

            std::cout << "\t Expected value: " << value 
                    << "\tComputed value: " << result 
                    << "\t" << (check_result ? "OK" : "NOT PASSED") 
                    << std::endl;

            assert(check_result);
        }
    }
}

// Invalid expressions
// Exceptions are expected
std::vector <std::string> math_bad_expressions = {
    "a == 10",
    "a_1! = 10",
    "_a1! = 5",
    "deg(3.14/4",
    "sinha(3.5)*2",
    "5/(1-1)",
    "2*4.5-4,9",
    "{PI} = 10",
    "1/++2,2+4",
    "(((10+11*2)*((2+1)*3)+8)"
};

void check_math_bad_expressions(void)
{
    std::map<std::string, double> local_variables;
    std::map<std::string, double> constants = {
        {"PI", 3.14}
    };

    std::cout << "Bad math expressions evaluation test: " << std::endl;

    // Every expression should lead to exception
    // No exception -> no test pass
    for (auto &expr : math_bad_expressions)
    {
        VarAssigner var_assigner(local_variables, constants);
        BaseCalculator base_calc(local_variables, constants);

        std::cout << "Parsing: '" << expr << "'";

        if (expr.find('=') != std::string::npos) // Assignment, if the expression contains '=' character
        {
            auto string_start = expr.begin();
            auto string_end = expr.end();

            try {
                var_assigner.AssignVar(expr);
            }
            catch (const std::exception &e) {
                std::cout << "\tcaught: '" << e.what() << "'\tOK" << std::endl;
                continue;
            }
        }
        else // Direct calculation
        {
            try {
                double result = base_calc.EvaluateMathExpression(expr);
                std::cout << "\tResult = " << result;
            }
            catch (const std::exception &e) {
                std::cout << "\tcaught: '" << e.what() << "'\tOK" << std::endl;
                continue;
            }
        }

        std::cout << "\n\n\nNo error found for: '" << expr << "'!!!" << std::endl;
        assert(0); // Error wasn't caught
    }
}

bool equal(double first, double second)
{
    return std::fabs(first - second) / second * 100 <= ALLOWABLE_MARGIN_IN_PERCENT;
}