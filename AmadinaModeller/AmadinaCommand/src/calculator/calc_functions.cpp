#include "calculator/calc_functions.h"
#include <math.h>

void cad::command::interpreter::grammar::calc::init_default_unary_functions(unary_function_t *b_func)
{
    b_func->add_function("abs", static_cast<double (*)(double)>(abs));
    b_func->add_function("acos", static_cast<double (*)(double)>(acos));
    b_func->add_function("asin", static_cast<double (*)(double)>(asin));
    b_func->add_function("atan", static_cast<double (*)(double)>(atan));
    b_func->add_function("cos", static_cast<double (*)(double)>(cos));
    b_func->add_function("cosh", static_cast<double (*)(double)>(cosh));
    b_func->add_function("exp", static_cast<double (*)(double)>(exp));
    b_func->add_function("log", static_cast<double (*)(double)>(log));
    b_func->add_function("log10", static_cast<double (*)(double)>(log10));
    b_func->add_function("sin", static_cast<double (*)(double)>(sin));
    b_func->add_function("sinh", static_cast<double (*)(double)>(sinh));
    b_func->add_function("sqrt", static_cast<double (*)(double)>(sqrt));
    b_func->add_function("tan", static_cast<double (*)(double)>(tan));
    b_func->add_function("tanh", static_cast<double (*)(double)>(tanh));
}

void cad::command::interpreter::grammar::calc::init_default_binary_functions(binary_function_t *u_func)
{
    u_func->add_function("pow", static_cast<double (*)(double, double)>(pow));
}
