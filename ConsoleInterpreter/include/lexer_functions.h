#ifndef LEXER_FUNCTIONS_H_INCLUDED
#define LEXER_FUNCTIONS_H_INCLUDED

namespace cad
{
    namespace command
    {
        typedef double (*lexer_function_t)(double);

        void lexer_functions_init(void);

        void lexer_set_angle_units(bool is_degree);
    }
}

#endif // LEXER_FUNCTIONS_H_INCLUDED
