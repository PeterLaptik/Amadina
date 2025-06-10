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

void check_math_calcultions(void);
void check_math_bad_expressions(void);
void check_command_line_expressions(void);
void test_command(void);

void indent()
{
    std::cout << std::endl << std::endl;
}

int main()
{
    // Grammar evaluator and parser tests
    std::cout << "Start parser tests";

    indent();
    try {
        //check_math_calcultions();
    } catch (const std::exception &e) {
        std::cout << std::endl << "Error: " << e.what() << std::endl;
        return 1;
    }
    
    indent();
    //check_math_bad_expressions();

    indent();
    try {
        //check_command_line_expressions();
    }
    catch (const std::exception &e) {
        std::cout << std::endl << "Error: " << e.what() << std::endl;
        return 1;
    }

    indent();
    test_command();
    
    // Command interpreter tests

    return 0;
}


