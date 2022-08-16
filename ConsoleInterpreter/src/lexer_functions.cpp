#include <math.h>
#include "../include/lexer_functions.h"
#include "../include/lexer.h"

typedef cad::command::LexerError LexerError;

double fn_sqrt(double x);
double fn_sin(double x);
double fn_cos(double x);
double fn_tan(double x);
double fn_ctan(double x);
double fn_asin(double x);
double fn_acos(double x);

void cad::command::lexer_functions_init()
{
    Lexer::AddFunction("sqrt", &fn_sqrt);
    Lexer::AddFunction("sin", &fn_sin);
    Lexer::AddFunction("cos", &fn_cos);
    Lexer::AddFunction("tan", &fn_tan);
    Lexer::AddFunction("cotan", &fn_ctan);
    Lexer::AddFunction("asin", &fn_asin);
    Lexer::AddFunction("acos", &fn_acos);
}

double fn_sqrt(double x)
{
    if(x<0)
        throw LexerError("Wrong value for square root argument: " + std::to_string(x));

    return sqrt(x);
}

double fn_sin(double x)
{
    return sin(x);
}

double fn_cos(double x)
{
    return cos(x);
}

double fn_tan(double x)
{
    return tan(x);
}

double fn_ctan(double x)
{
    return 1/tan(x);
}

double fn_asin(double x)
{
    return asin(x);
}

double fn_acos(double x)
{
    return acos(x);
}
