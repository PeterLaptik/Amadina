#ifndef COMMAND_FUNCTIONS_DEF_H_INCLUDED
#define COMMAND_FUNCTIONS_DEF_H_INCLUDED

namespace cad::command::interpreter
{
    typedef double (*lexer_function_unary_pt_t)(double);
    typedef double (*lexer_function_binary_pt_t)(double, double);
}

#endif // COMMAND_FUNCTIONS_DEF_H_INCLUDED
