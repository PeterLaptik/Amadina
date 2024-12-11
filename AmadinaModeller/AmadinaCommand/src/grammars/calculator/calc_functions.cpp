#include "grammars/calculator/calc_functions.h"
#include <math.h>
#include <map>

const double PI = 3.14159;

double rad_from_deg(double val);
double deg_from_rad(double val);

void cad::command::interpreter::grammar::calc::init_default_unary_functions(unary_function_t *b_func)
{
    b_func->add_function("abs", static_cast<lexer_function_unary_pt_t>(abs));
    b_func->add_function("acos", static_cast<lexer_function_unary_pt_t>(acos));
    b_func->add_function("asin", static_cast<lexer_function_unary_pt_t>(asin));
    b_func->add_function("atan", static_cast<lexer_function_unary_pt_t>(atan));
    b_func->add_function("cos", static_cast<lexer_function_unary_pt_t>(cos));
    b_func->add_function("cosh", static_cast<lexer_function_unary_pt_t>(cosh));
    b_func->add_function("exp", static_cast<lexer_function_unary_pt_t>(exp));
    b_func->add_function("log", static_cast<lexer_function_unary_pt_t>(log));
    b_func->add_function("log10", static_cast<lexer_function_unary_pt_t>(log10));
    b_func->add_function("sin", static_cast<lexer_function_unary_pt_t>(sin));
    b_func->add_function("sinh", static_cast<lexer_function_unary_pt_t>(sinh));
    b_func->add_function("sqrt", static_cast<lexer_function_unary_pt_t>(sqrt));
    b_func->add_function("tan", static_cast<lexer_function_unary_pt_t>(tan));
    b_func->add_function("tanh", static_cast<lexer_function_unary_pt_t>(tanh));
    b_func->add_function("rad", static_cast<lexer_function_unary_pt_t>(&rad_from_deg));
    b_func->add_function("deg", static_cast<lexer_function_unary_pt_t>(&deg_from_rad));
}

void cad::command::interpreter::grammar::calc::init_default_binary_functions(binary_function_t *u_func)
{
    u_func->add_function("pow", static_cast<lexer_function_binary_pt_t>(pow));
}

double rad_from_deg(double val)
{
    return val * PI / 180;
}

double deg_from_rad(double val)
{
    return val * 180 / PI;
}