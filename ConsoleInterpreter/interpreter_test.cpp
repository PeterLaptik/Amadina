#include "include/lexer.h"
#include "include/interpreter.h"
#include <iostream>
#include <map>
#include <cfloat>
#include <assert.h>
#include <limits>

using cad::command::Lexer;
using cad::command::Interpreter;

void test_expressions(void);
void test_interpreter(void);

const double ALLOWABLE_TOLERANCE = 0.01;

int main(int argc, char **argv)
{
    std::cout << "*********************************" << std::endl;
    std::cout << "Console command interpreter test." << std::endl;
    std::cout << "*********************************" << std::endl;

    std::cout << std::endl << "Testing... Expressions evaluations." << std::endl;
    std::cout << std::endl << "Allowable tolerances: ";
    std::cout << ALLOWABLE_TOLERANCE*100 << "%" << std::endl;

    //test_expressions();

    std::cout << std::endl << "Testing... Interpreter parsing." << std::endl;
    test_interpreter();

    std::cout << std::endl;
    std::cout << "*********************************" << std::endl;
    std::cout << "Tests are finished successfully." << std::endl;
    std::cout << "*********************************" << std::endl;
    return 0;
}



/**************************************************************/
/***************   Expressions tests   ************************/
/**************************************************************/
std::map<std::string,double> expr_examples = {
    {"0  ", 0},
    {"10", 10},
    {"5+5", 10},
    {"1+2", 3},
    {"20.5+10*2", 40.5},
    {"20.5+(10*2)", 40.5},
    {"(20.5+10)*2", 61},
    {"4/10+2*(4+1)", 10.4},
    {"-8+2*4.1", 0.20},
    {"(-4+(5-9))*2.5+2.25*2", -15.5},
    {"-200*(2+1)", -600},
    {"50+((10-15)*0.3)", 48.5},
    {"10*((10-15)*0.3)", -15},
    {"0*25+4*0", 0},
    {"-1+1", 0},
};

void test_expressions()
{
    // Maximum size of expression string-value
    size_t max_size = 0;
    for(auto &expr: expr_examples)
        if(expr.first.size()>max_size)
            max_size = expr.first.size();

    // Size to align
    max_size++;

    Lexer lexer;
    double result = 0.0;
    for(auto &expr: expr_examples)
    {
        result = lexer.Evaluate(expr.first);
        std::string expression = expr.first;
        expression.append(max_size - expression.size(), ' '); // align
        std::cout << expression << " = " << result;
        std::cout << "\texpected value: " << expr.second;
        if(expr.second!=0)
            assert(fabs((result - expr.second)/result) < ALLOWABLE_TOLERANCE);
        else
            assert(fabs(result - expr.second) <= DBL_EPSILON);
        std::cout << "\tOK" << std::endl;
    }
}

void test_interpreter()
{
    Interpreter interpreter;
    interpreter.ParseExpression("line 10,10 x \t20 , 20");
}
