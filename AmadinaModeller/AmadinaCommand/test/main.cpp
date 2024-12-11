#include "command_parser.h"
#include "grammars/variables/var_assigner.h"
#include "grammars/calculator/base_calculator.h"
#include "parser_exception.h"
#include "grammars/variables/var_grammar.h"
#include "grammars/calculator/calc_grammar.h"
#include "grammars/calculator/calc_evaluator.h"
#include "grammars/command_line/command_grammar.h"
#include "assert.h"
#include <boost/spirit/home/x3.hpp>
#include <iostream>

using cad::command::interpreter::grammar::variables::VarAssigner;
using cad::command::interpreter::grammar::calc::BaseCalculator;

void check_math_calcultions(void);
void check_math_bad_expressions(void);
void check_command_line_expressions(void);
std::string token_to_string(const cad::command::interpreter::CommandToken &tk);
bool equal(double first, double second);


const double ALLOWABLE_MARGIN_IN_PERCENT = 1;


int main()
{
    std::cout << std::endl << "Start testing..." << std::endl;

    try {
        check_math_calcultions();
    } catch (const std::exception &e) {
        std::cout << std::endl << "Error: " << e.what() << std::endl;
        return 1;
    }
    
    check_math_bad_expressions();

    try {
        check_command_line_expressions();
    }
    catch (const std::exception &e) {
        std::cout << std::endl << "Error: " << e.what() << std::endl;
        return 1;
    }
    

    return 0;
}

std::vector<std::string> test_line_commands = {
    "LINE [0,0] [10, 10.5, 15.1] \"Sketch_1\" xFlag",
    "   Circle [10,10+5, 15.4]  \"Sketch_2\" r15   ",
    "bOx (1.5*2/3+cos(rad(0)))",
    "command x (15+4)",
    " command x (15+4) ",
    "  command x (15+4)  ",
};

void check_command_line_expressions(void)
{
    using cad::command::interpreter::CommandToken;
    cad::command::interpreter::CommandParser parser;

    std::cout << "\n\nMain parser test: " << std::endl;

    for (auto &expr : test_line_commands)
    {

        std::cout << "Command line: '" << expr << "'\t";
        bool res = parser.ParseCommand(expr);
        if (!res)
            throw std::exception(parser.GetResultMessage().c_str());

        // Has tokens?
        bool is_empty = parser.IsEmpty();
        assert(!is_empty);

        size_t tokens_number = parser.GetTokensNumber();
        for (int i = 0; i < tokens_number; i++)
        {
            const CommandToken &tk = parser.GetToken(i);
            std::cout << token_to_string(tk) << "\t";

            // List size check
            if (tk.IsList())
                assert(tk.GetListSize());

            // Text forced lowercase characters check
            if (tk.IsText())
            {
               std::string lower_txt;
                std::transform(tk.GetStringValue().begin(), tk.GetStringValue().end(), std::back_inserter(lower_txt),
                    [](auto ch) {
                        return std::tolower(ch);
                    });

                assert(lower_txt == tk.GetStringValue());
            }
        }
        std::cout << std::endl;
    }
}

std::string token_to_string(const cad::command::interpreter::CommandToken &tk)
{
    std::string result;
    if (tk.IsText())
    {
        result += ("txt: " + tk.GetStringValue());
    }

    if (tk.IsString())
    {
        result += ("str: " + tk.GetStringValue());
    }

    if (tk.IsNumeric())
    {
        result += ("num: " + std::to_string(tk.GetNumericValue()));
    }

    if (tk.IsList())
    {
        result += "[";
        size_t list_size = tk.GetListSize();
        for (int i = 0; i < list_size; i++)
        {
            result += std::to_string(tk.Get(i));
            result += (i != list_size - 1 ? ", " : "");
        }
        result += "]";
    }

    return result;
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
    std::map<std::string, double> local_variables;
    std::map<std::string, double> constants = {
        {"PI", 3.14}
    };

    std::cout << "\n\nMath expressions test: " << std::endl;
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
            std::cout << "\t Expected value: " << value << "\tComputed value: " << result << "\t" << (check_result ? "OK" : "NOT PASSED") << std::endl;
            assert(check_result);
        }
    }
}

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

    std::cout << "\n\nBad math expressions test: " << std::endl;
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
            } catch (const std::exception &e) {
                std::cout << "\tcaught: '" << e.what() << "'\tOK" << std::endl;
                continue;
            }
        }
        else // Direct calculation
        {
            try {
                double result = base_calc.EvaluateMathExpression(expr);
                std::cout << "\tResult = " << result;
            } catch (const std::exception &e) {
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