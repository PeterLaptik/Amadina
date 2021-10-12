#include "interpreter.h"
#include "lexer.h"
#include <iostream>
#include <string.h>
#include <assert.h>

void test_interpreter(void);
void test_lexer(void);
void output_point(const Point &p);

int main(int argc, char **argv)
{
//    test_lexer();
    test_interpreter();
    return 0;
}

void test_interpreter()
{
    Interpreter interpreter;
    std::string expression = "line 10,10,5/2 8.2,4.5+0.5,(18-10)*2";
    interpreter.Interpretate(expression);

    std::cout<<"Expression: "<<expression<<std::endl;
    int num = interpreter.GetTokensNumber();
    assert(num==3);
    Token t = interpreter.GetFirstToken();
    assert(t.IsString()==true);
    std::cout<<"Command:"<<t.GetString()<<std::endl;
    // point 1
    t = interpreter.GetNextToken();
    assert(t.IsPoint());
    output_point(t.GetPoint());
    // point 2
    t = interpreter.GetNextToken();
    assert(t.IsPoint());
    output_point(t.GetPoint());
    assert(interpreter.HasNextToken()==false);

    try
    {
        t = interpreter.GetNextToken();
    }
    catch(const std::exception &e)
    {
        std::cout<<"OK... Exception caught. "<<e.what()<<std::endl;
    }

    expression = "circle 10,10,4 5";
    std::cout<<"Expression: "<<expression<<std::endl;
    interpreter.Interpretate(expression);
    num = interpreter.GetTokensNumber();
    assert(num==3);
    t = interpreter.GetFirstToken();
    assert(t.IsString()==true);
    std::cout<<"Command:"<<t.GetString()<<std::endl;
    // point 1
    t = interpreter.GetNextToken();
    assert(t.IsPoint());
    output_point(t.GetPoint());
    // radius
    t = interpreter.GetNextToken();
    assert(t.IsNumber());
    std::cout<<"Radius:"<<t.GetNumber()<<std::endl;

    expression = "circle 10,10+4,4 50/2.5";
    std::cout<<"Expression: "<<expression<<std::endl;
    interpreter.Interpretate(expression);
    num = interpreter.GetTokensNumber();
    assert(num==3);
    t = interpreter.GetFirstToken();
    assert(t.IsString()==true);
    std::cout<<"Command:"<<t.GetString()<<std::endl;
    // point 1
    t = interpreter.GetNextToken();
    assert(t.IsPoint());
    output_point(t.GetPoint());
    // radius
    t = interpreter.GetNextToken();
    assert(t.IsNumber());
    std::cout<<"Radius:"<<t.GetNumber()<<std::endl;

    expression = "    circle      0,0,0     2*5    ";
    std::cout<<"Expression: "<<expression<<std::endl;
    interpreter.Interpretate(expression);
    num = interpreter.GetTokensNumber();
    assert(num==3);
    t = interpreter.GetFirstToken();
    assert(t.IsString()==true);
    std::cout<<"Command:"<<t.GetString()<<std::endl;
    // point 1
    t = interpreter.GetNextToken();
    assert(t.IsPoint());
    output_point(t.GetPoint());
    // radius
    t = interpreter.GetNextToken();
    assert(t.IsNumber());
    std::cout<<"Radius:"<<t.GetNumber()<<std::endl;

    expression = "    circle      100,-5,-15/10     -3.1/2    ";
    std::cout<<"Expression: "<<expression<<std::endl;
    interpreter.Interpretate(expression);
    num = interpreter.GetTokensNumber();
    assert(num==3);
    t = interpreter.GetFirstToken();
    assert(t.IsString()==true);
    std::cout<<"Command:"<<t.GetString()<<std::endl;
    // point 1
    t = interpreter.GetNextToken();
    assert(t.IsPoint());
    output_point(t.GetPoint());
    // radius
    t = interpreter.GetNextToken();
    assert(t.IsNumber());
    std::cout<<"Radius:"<<t.GetNumber()<<std::endl;
}

void output_point(const Point &p)
{
    double x = p.GetX();
    double y = p.GetY();
    double z = p.GetZ();
    std::cout<<"point: "<<x<<", "<<y<<", "<<z<<std::endl;
}

void test_lexer(void)
{
    std::string expression;
    double right_value;
    double result;

    Lexer lexer;
    std::cout<<"Lexer testing..."<<std::endl;
    expression = "3+5"; right_value = 8;
    std::cout<<"testing "<<expression<<"="<<right_value;
    result = lexer.Evaluate(expression);
    assert(right_value==result);
    std::cout<<" ...OK"<<std::endl;

    expression = "3+5;"; right_value = 8;
    std::cout<<"testing "<<expression<<"="<<right_value;
    result = lexer.Evaluate(expression);
    assert(right_value==result);
    std::cout<<" ...OK"<<std::endl;

    expression = "3+5;;"; right_value = 8;
    std::cout<<"testing "<<expression<<"="<<right_value;
    result = lexer.Evaluate(expression);
    assert(right_value==result);
    std::cout<<" ...OK"<<std::endl;

    expression = "5*2+4*2"; right_value = 18;
    std::cout<<"testing "<<expression<<"="<<right_value;
    result = lexer.Evaluate(expression);
    assert(right_value==result);
    std::cout<<" ...OK"<<std::endl;

    expression = "5*(2+4)*2"; right_value = 60;
    std::cout<<"testing "<<expression<<"="<<right_value;
    result = lexer.Evaluate(expression);
    assert(right_value==result);
    std::cout<<" ...OK"<<std::endl;

    expression = "5*(2+4)+2"; right_value = 32;
    std::cout<<"testing "<<expression<<"="<<right_value;
    result = lexer.Evaluate(expression);
    assert(right_value==result);
    std::cout<<" ...OK"<<std::endl;

    expression = "5-(2+4)+2"; right_value = 1;
    std::cout<<"testing "<<expression<<"="<<right_value;
    result = lexer.Evaluate(expression);
    assert(right_value==result);
    std::cout<<" ...OK"<<std::endl;

    expression = "1.8"; right_value = 1.8;
    std::cout<<"testing "<<expression<<"="<<right_value;
    result = lexer.Evaluate(expression);
    assert(right_value==result);
    std::cout<<" ...OK"<<std::endl;

    expression = "-5"; right_value = -5;
    std::cout<<"testing "<<expression<<"="<<right_value;
    result = lexer.Evaluate(expression);
    assert(right_value==result);
    std::cout<<" ...OK"<<std::endl;

    expression = "10"; right_value = 10;
    std::cout<<"testing "<<expression<<"="<<right_value;
    result = lexer.Evaluate(expression);
    assert(right_value==result);
    std::cout<<" ...OK"<<std::endl;

    try
    {
        expression = "5-(2/0)+2"; right_value = 1;
        result = lexer.Evaluate(expression);
        assert(right_value==result);
    }
    catch (const std::exception &e)
    {
        std::cout<<"testing exception...OK. Exception caught: "<<e.what()<<std::endl;
    }
    std::cout<<"Lexer tested. OK"<<std::endl;
}
