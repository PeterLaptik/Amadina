#include <math.h>
#include "../include/lexer_functions.h"
#include "../include/lexer.h"


double fn_sqrt(double x);

void cad::command::lexer_functions_init()
{
    Lexer::AddFunction("sqrt", &fn_sqrt);
}

double fn_sqrt(double x)
{
    return sqrt(x);
}
