#ifndef CALC_FUNCTIONS_H_INCLUDED
#define CALC_FUNCTIONS_H_INCLUDED

#include "calculator/calc_ast.h"
#include <boost/spirit/home/x3.hpp>

namespace cad::command::interpreter::grammar::calc
{
    struct unary_function_t;
    struct binary_function_t;

    void init_default_unary_functions(unary_function_t *b_func);
    void init_default_binary_functions(binary_function_t *u_func);

    struct unary_function_t: boost::spirit::x3::symbols<lexer_function_unary_pt_t>
    {
            unary_function_t()
            {
                init();
            }

            void reset()
            {
                clear();
                init();
            }

            void add_function(std::string name, lexer_function_unary_pt_t p)
            {
                add(name, p);
            }

        private:
            void init()
            {
                init_default_unary_functions(this);
            }
    };

    struct binary_function_t: boost::spirit::x3::symbols<lexer_function_binary_pt_t>
    {
            binary_function_t()
            {
                init();
            }

            void reset()
            {
                clear();
                init();
            }

            void add_function(std::string name, lexer_function_binary_pt_t p)
            {
                add(name, p);
            }

        private:
            void init()
            {
                init_default_binary_functions(this);
            }
    };
}

#endif // CALC_FUNCTIONS_H_INCLUDED
