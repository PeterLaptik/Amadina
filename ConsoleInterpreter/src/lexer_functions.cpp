#define _USE_MATH_DEFINES

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
double convert_angle_to_deg(double x);

static bool lexer_angle_use_degree = true;

void cad::command::lexer_functions_init()
{
    lexer_angle_use_degree = false;
    Lexer::AddFunction("sqrt", &fn_sqrt);
    Lexer::AddFunction("sin", &fn_sin);
    Lexer::AddFunction("cos", &fn_cos);
    Lexer::AddFunction("tan", &fn_tan);
    Lexer::AddFunction("cotan", &fn_ctan);
    Lexer::AddFunction("asin", &fn_asin);
    Lexer::AddFunction("acos", &fn_acos);
}

void cad::command::lexer_set_angle_units(bool is_degree)
{
    lexer_angle_use_degree = is_degree;
}

double fn_sqrt(double x)
{
    if(x<0)
        throw LexerError("Wrong value for square root argument: " + std::to_string(x));

    return sqrt(x);
}

double fn_sin(double x)
{
    return sin(convert_angle_to_deg(x));
}

double fn_cos(double x)
{
    return cos(convert_angle_to_deg(x));
}

double fn_tan(double x)
{
    return tan(convert_angle_to_deg(x));
}

double fn_ctan(double x)
{
    return 1/tan(convert_angle_to_deg(x));
}

double fn_asin(double x)
{
    return convert_angle_to_deg(asin(x));
}

double fn_acos(double x)
{
    return convert_angle_to_deg(acos(x));
}


double convert_angle_to_deg(double x)
{
    if(!lexer_angle_use_degree)
        return x;

    return M_PI*x/180;
}
