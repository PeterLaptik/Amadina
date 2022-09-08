#define _USE_MATH_DEFINES

#include "../include/lexer_math_functions.h"
#include "../include/lexer.h"
#include <math.h>

using cad::command::deg_to_rad;
using cad::command::rad_to_deg;
using LexerError = cad::command::LexerError;


// Default math functions for interpreter
double fn_sqrt(double x);
double fn_sin(double x);
double fn_cos(double x);
double fn_tan(double x);
double fn_ctan(double x);
double fn_asin(double x);
double fn_acos(double x);


// Keeps state of degrees / radians mode.
// If the flag is true then incoming and out-coming angle values are expected in degrees units
static bool lexer_degree_mode = true;


// Default functions available in interpretor
void cad::command::lexer_functions_init()
{
    lexer_degree_mode = false;
    Lexer::AddFunction("sqrt", &fn_sqrt);
    Lexer::AddFunction("sin", &fn_sin);
    Lexer::AddFunction("cos", &fn_cos);
    Lexer::AddFunction("tan", &fn_tan);
    Lexer::AddFunction("cotan", &fn_ctan);
    Lexer::AddFunction("asin", &fn_asin);
    Lexer::AddFunction("acos", &fn_acos);
    Lexer::AddConstant("pi", M_PI);
    Lexer::AddConstant("e", M_E);

}

// Sets degree / radian mode for functions
void cad::command::lexer_set_use_degree_units(bool is_degree)
{
    lexer_degree_mode = is_degree;
}

double fn_sqrt(double x)
{
    if(x<0)
        throw LexerError("Wrong value for square root argument: " + std::to_string(x));

    return sqrt(x);
}

double fn_sin(double x)
{
    return sin(deg_to_rad(x));
}

double fn_cos(double x)
{
    return cos(deg_to_rad(x));
}

double fn_tan(double x)
{
    return tan(deg_to_rad(x));
}

double fn_ctan(double x)
{
    return 1/tan(deg_to_rad(x));
}

double fn_asin(double x)
{
    if(x>1 || x<-1)
        throw LexerError("Wrong value for arcsin argument: " + std::to_string(x));

    return rad_to_deg(asin(x));
}

double fn_acos(double x)
{
    if(x>1 || x<-1)
        throw LexerError("Wrong value for arccos argument: " + std::to_string(x));

    return rad_to_deg(acos(x));
}

double cad::command::deg_to_rad(double x)
{
    if(!lexer_degree_mode)
        return x;

    return M_PI*x/180;
}

double cad::command::rad_to_deg(double x)
{
    if(!lexer_degree_mode)
        return x;

    return x*180/M_PI;
}

