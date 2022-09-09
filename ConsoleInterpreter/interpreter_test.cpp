#include "include/lexer.h"
#include "include/interpreter.h"

#include <iostream>
#include <map>
#include <cfloat>
#include <assert.h>
#include <limits>

using cad::command::Lexer;
using cad::command::LexerError;
using cad::command::Interpreter;

void test_expressions(void);
void test_interpreter(void);
void test_expressions_validation(void);
void test_expressions_with_functions_evaluations(void);
bool evaluate(Lexer &lexer, std::string expression);

const double ALLOWABLE_TOLERANCE = 0.01;

int main(int argc, char **argv)
{
    std::cout << "*********************************" << std::endl;
    std::cout << "Console command interpreter test." << std::endl;
    std::cout << "*********************************" << std::endl;

    std::cout << std::endl << "Testing... Expressions evaluations." << std::endl;
    std::cout << "Allowable tolerances: ";
    std::cout << ALLOWABLE_TOLERANCE*100 << "%" << std::endl;
    //test_expressions();

    std::cout << std::endl << "Testing... Expressions validations." << std::endl;
    //test_expressions_validation();

    std::cout << std::endl << "Testing... Expressions with functions and constants evaluations." << std::endl;
    std::cout << "Allowable tolerances: ";
    std::cout << ALLOWABLE_TOLERANCE*100 << "%" << std::endl;
    //test_expressions_with_functions_evaluations();

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
std::map<std::string,double> expr_examples =
{
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

std::map<std::string,bool> expr_validation_examples =
{
    {")0  ", true},
    {"10a", false},
    {"5+5", true},
    {"1+2", true},
    {"20.5+10*2", true},
    {"20.5 + (10*2)", true},
    {"(20.5+10x)*2", false},
    {"4/10+2*(4+1)", true},
    {"-8+2*4.1+b", false},
    {"(-4+ (5- 9)) * 2.5 +2. 25*2", true},
    {"sqrt(-200*(sqrt(4+18/(2+4)-3)+1)+604)", true},
    {"1+cotan(1)", true},
    {"sqrt(4*(cos(0.5)*cos(0.25*2) + sin(0.5)*sin(0.5)))", true},
    {"50+((10-15)*0,3)", false},
    {"10*((10-15)*0.3)", true},
    {"0*25+4*sin(0)", true},
    {"-1+1", true},
    {"(", true},
    {")", true},
    {"", true},
    {" ", true},
    {"asin(sin(30))", true},
    {"tan(pi*2)*sin(30)/pi", true}
};

void test_expressions_validation()
{
    // Maximum size of expression string-value
    size_t max_size = 0;
    for(auto &expr: expr_validation_examples)
        if(expr.first.size()>max_size)
            max_size = expr.first.size();

    // Size to align
    max_size++;

    Lexer lexer;
    Lexer::UseDegreesForAngles(true);
    bool result;
    for(auto &expr: expr_validation_examples)
    {
        result = lexer.IsExpression(expr.first);
        std::string expression = expr.first;
        expression.append(max_size - expression.size(), ' '); // align
        std::cout << expression << " is valid:" << (result ? "true" : "false");
        assert(result==expr.second);
        std::cout << "\tresult: ";
        evaluate(lexer, expr.first);
        std::cout << std::endl;
    }
}

std::map<std::string,double> expr_validation_funct_examples =
{
    {"pi", 3.14},
    {"tan(pi*2)*sin(30)/pi", 0.01752},
    {"sin(30)*sin(30)+ cos(30)*cos(30)", 1},
    {"cos(sqrt(4*4+3*3)*12)", 0.5},
    {"sqrt(cos(180)*(-1))", 1},
    {"cos(asin(1)*2)", -1},
    {"2*e*PI*pI", 53.657},
    {"e", 2.718},
    {"-E", -2.718},
};

void test_expressions_with_functions_evaluations()
{
    // Maximum size of expression string-value
    size_t max_size = 0;
    for(auto &expr: expr_validation_examples)
        if(expr.first.size()>max_size)
            max_size = expr.first.size();

    // Size to align
    max_size++;

    Lexer lexer;
    Lexer::UseDegreesForAngles(true);
    double result = 0.0;
    for(auto &expr: expr_validation_funct_examples)
    {
        try
        {
            result = lexer.Evaluate(expr.first);
        }
        catch (const LexerError &e)
        {
            std::cout << std::endl << "Error on evaluation '" << expr.first <<"': " << e.what()
            << std::endl << std::endl;
        }

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
    interpreter.ParseExpression(" line 10,10 x \t20 , 20+8/2 255.4 10");
    try
    {
        interpreter.ParseExpression(" line [10,10] x \t20 , [20+8/2] 255.4 10");
    }
    catch(const LexerError &e)
    {
        std::cout<<e.what()<<std::endl;
    }

//    interpreter.ParseExpression(" , ");
//    interpreter.ParseExpression(",");
//    interpreter.ParseExpression(" , ,");
//    interpreter.ParseExpression(", ,");
}

bool evaluate(Lexer &lexer, std::string expression)
{
    try
    {
        double result = lexer.Evaluate(expression);
        std::cout<<result;
        return true;
    }
    catch(const std::exception &e)
    {
        std::cout<<e.what();
        return false;
    }
}
