#ifndef INTERPRETER_LEXER_H_INCLUDED
#define INTERPRETER_LEXER_H_INCLUDED

#include "calc_ast.h"
#include <vector>

namespace cad::command::interpreter::grammar::calc
{
    class Lexer
    {
        public:
            typedef void result_type;

            Lexer(std::vector<double>& code);
            ~Lexer() = default;

            void operator()(ast::nil) const;
            void operator()(double n) const;
            void operator()(ast::operation const& x) const;
            void operator()(ast::signed_ const& x) const;
            void operator()(ast::math_expression const& x) const;
            void operator()(ast::variable const& x) const;
            void operator()(ast::function_unary const& x) const;
            void operator()(ast::function_binary const& x) const;
            void Show();

        private:
            std::vector<double>& code;
    };
}
#endif // INTERPRETER_LEXER_H_INCLUDED
