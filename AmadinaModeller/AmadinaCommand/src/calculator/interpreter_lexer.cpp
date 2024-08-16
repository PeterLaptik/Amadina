#include "calculator/calc_lexer.h"
#include "calculator/calc_operations.h"

cad::command::interpreter::grammar::calc::Lexer::Lexer(std::vector<double>& code)
    : code(code)
{ }

void cad::command::interpreter::grammar::calc::Lexer::operator()(ast::nil) const
{
    BOOST_ASSERT(0);
}

void cad::command::interpreter::grammar::calc::Lexer::operator()(double n) const
{
    code.push_back(op_num);
    code.push_back(n);
}

void cad::command::interpreter::grammar::calc::Lexer::operator()(ast::operation const& x) const
{
    boost::apply_visitor(*this, x.operand_);
    switch (x.operator_)
    {
    case '+':
        code.push_back(op_add);
        break;
    case '-':
        code.push_back(op_sub);
        break;
    case '*':
        code.push_back(op_mul);
        break;
    case '/':
        code.push_back(op_div);
        break;
    default:
        BOOST_ASSERT(0);
        break;
    }
}

void cad::command::interpreter::grammar::calc::Lexer::operator()(ast::signed_ const& x) const
{
    boost::apply_visitor(*this, x.operand_);
    switch (x.sign)
    {
    case '-':
        code.push_back(op_neg);
        break;
    case '+':
        break;
    default:
        BOOST_ASSERT(0);
        break;
    }
}

void cad::command::interpreter::grammar::calc::Lexer::operator()(ast::math_expression const& x) const
{
    boost::apply_visitor(*this, x.first);
    for (ast::operation const& oper : x.rest)
    {
        (*this)(oper);
    }
}

void cad::command::interpreter::grammar::calc::Lexer::operator()(ast::variable const& x) const
{
    std::cout << "Found variable" << x.name << std::endl;
}

void cad::command::interpreter::grammar::calc::Lexer::operator()(ast::function_unary const& x) const
{
    std::cout << "Found function" << std::endl;
//    boost::apply_visitor(*this, x.first);
//    code.push_back(op_fnu);
//    code.push_back(function_unary.name);
//    code.push_back(function_unary.arg);
}

void cad::command::interpreter::grammar::calc::Lexer::operator()(ast::function_binary const& x) const
{
    std::cout << "Found function binary" << std::endl;
//    boost::apply_visitor(*this, x.first);
//    code.push_back(op_fnu);
//    code.push_back(function_unary.name);
//    code.push_back(function_unary.arg);
}

void cad::command::interpreter::grammar::calc::Lexer::Show()
{

}
