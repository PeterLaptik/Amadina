#ifndef INTERPRETER_EVALUATOR_H_INCLUDED
#define INTERPRETER_EVALUATOR_H_INCLUDED

#include "calc_ast.h"
#include <map>

namespace cad::command::interpreter::grammar::calc::exec
{
    using cad::command::interpreter::grammar::calc::ast::Operation;
    using cad::command::interpreter::grammar::calc::ast::Signed;
    using cad::command::interpreter::grammar::calc::ast::MathExpression;
    using cad::command::interpreter::grammar::calc::ast::Variable;
    using cad::command::interpreter::grammar::calc::ast::FunctionUnary;
    using cad::command::interpreter::grammar::calc::ast::FunctionBinary;

    class Evaluator
    {
        public:
            Evaluator(std::map<std::string, double> &vars_list, 
                            std::map<std::string, double> &const_list);

            double operator()(double n) const;
            double operator()(double lhs, const Operation &x) const;
            double operator()(const Variable &var) const;
            double operator()(const FunctionUnary &fn) const;
            double operator()(const FunctionBinary &fn) const;
            double operator()(const Signed &x) const;
            double operator()(const MathExpression &x) const;

        private:
            std::map<std::string, double> &m_variables;
            std::map<std::string, double> &m_constants;
    };
}

#endif // INTERPRETER_EVALUATOR_H_INCLUDED
