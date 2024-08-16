#ifndef INTERPRETER_EVALUATOR_H_INCLUDED
#define INTERPRETER_EVALUATOR_H_INCLUDED

#include "calc_ast.h"
#include <numeric>

namespace cad::command::interpreter::grammar::calc::exec
{
    using cad::command::interpreter::grammar::calc::ast::nil;
    using cad::command::interpreter::grammar::calc::ast::operation;
    using cad::command::interpreter::grammar::calc::ast::signed_;
    using cad::command::interpreter::grammar::calc::ast::math_expression;
    using cad::command::interpreter::grammar::calc::ast::variable;
    using cad::command::interpreter::grammar::calc::ast::function_unary;
    using cad::command::interpreter::grammar::calc::ast::function_binary;

    struct Evaluator
    {
        typedef double result_type;

        double operator()(nil) const
        {
            BOOST_ASSERT(0);
            return 0;
        }

        double operator()(double n) const
        {
            return n;
        }

        double operator()(double lhs, operation const& x) const
        {
            double rhs = boost::apply_visitor(*this, x.operand_);
            switch (x.operator_)
            {
            case '+':
                return lhs + rhs;
            case '-':
                return lhs - rhs;
            case '*':
                return lhs * rhs;
            case '/':
                return lhs / rhs;
            }
            BOOST_ASSERT(0);
            return 0;
        }

        double operator()(const variable &var) const
        {
            //double rhs = boost::apply_visitor(*this, var);
            std::cout << "Variable name: " << var.name << std::endl;
            //BOOST_ASSERT(0);
            return 1;
        }

        double operator()(const function_unary &fn) const
        {
            double rhs = boost::apply_visitor(*this, fn.arg);
//            std::cout << "FN un name: " << fn.name << std::endl;
            std::cout << "FN arg: " << rhs << std::endl;
            //BOOST_ASSERT(0);
            return fn.pointer(rhs);
        }

        double operator()(const function_binary &fn) const
        {
            std::cout << "FN bin: " << std::endl;

            double lhs = boost::apply_visitor(*this, fn.arg_1);
            double rhs = boost::apply_visitor(*this, fn.arg_2);
//            std::cout << "FN bin name: " << fn.name << std::endl;
            std::cout << "FN arg: " << rhs << std::endl;
            //BOOST_ASSERT(0);
            return fn.pointer(lhs,rhs);
        }

        double operator()(signed_ const& x) const
        {
            double rhs = boost::apply_visitor(*this, x.operand_);
            switch (x.sign)
            {
            case '-':
                return -rhs;
            case '+':
                return +rhs;
            }
            BOOST_ASSERT(0);
            return 0;
        }

        double operator()(math_expression const& x) const
        {
            return std::accumulate(x.rest.begin(), x.rest.end(),
                                   boost::apply_visitor(*this, x.first),
                                   *this);
        }
    };
}

#endif // INTERPRETER_EVALUATOR_H_INCLUDED
