//#define BOOST_TEST_MODULE test module name
//#include <boost/test/included/unit_test.hpp>
//
//
//using namespace boost::unit_test;
//
//
//BOOST_AUTO_TEST_SUITE(f_to_c)
//
//BOOST_AUTO_TEST_SUITE_END()

#include "command_interpreter.h"
#include "command_parser.h"
#include <iostream>
#include <map>
#include <math.h>
// LINE [5,10,15] D "xstring" {d}+1

void test_parsing();

using cad::command::interpreter::lexer_function_unary_t;
using cad::command::interpreter::lexer_function_binary_t;

int main()
{
    using cad::command::interpreter::CommandParser;

    std::map<std::string, double> variables;
    std::map<std::string, lexer_function_unary_t> unary_functions;
    std::map<std::string, lexer_function_binary_t> binary_functions;

    CommandParser cmd;

    std::string expr_valid = "rex(2, 3)";

    cmd.ParseCommand(expr_valid);

    std::cout << cmd.GetResultMessage() << std::endl;
    return 0;
}


void init_constants(std::map<std::string, double> variables)
{
    variables.insert(std::make_pair("PI", 3.14159));
    variables.insert(std::make_pair("e", 2.71828));
}

void test_parsing()
{
//    const char* expression = "LINE 10,10 0,0";
//    cad::command::interpreter::CommandInterpreter interpreter;
//    interpreter.ParseExpression(expression);
//
//    using cad::command::interpreter::grammar::expression_class;
//    using cad::command::interpreter::ast::expression;
//    using cad::command::interpreter::Evaluator;
//    using calc_t = boost::spirit::x3::rule<expression_class, expression, false>;
//
//    using cad::command::interpreter::ast::expression;
//
//    boost::spirit::x3::ascii::space_type space;
//
//    auto &calc = cad::command::interpreter::grammar::calculator;
//    expression res;
//    std::string e = "10+4*(9-5)"; // line 10, {x} 20,20
//    auto start = e.begin();
//    auto end = e.end();
//    bool r = phrase_parse(start, end, calc, space, res);
//
//    Evaluator eval;
//    if (r && start == end)
//    {
//        std::cout << "-------------------------\n";
//        std::cout << "Parsing succeeded\n";
//        std::cout << "\nResult: " << eval(res) << std::endl;
//        std::cout << "-------------------------\n";
//    }
//    else
//    {
//        std::cout << "-------------------------\n";
//        std::cout << "Parsing failed\n";
//        std::cout << "-------------------------\n";
//    }
}
