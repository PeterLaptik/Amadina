#include "../include/lexer.h"
#include <sstream>
#include <memory>
#include <iostream>

using Lexer = cad::command::Lexer;
using lexer_function_t = cad::command::lexer_function_t;

// Exceptions messages
const std::string ERR_MSG_BAD_TOKEN = "Lexer error. bad token:";
const std::string ERR_MSG_DIV_ZERO = "Lexer error. dividing by zero";
const std::string ERR_MSG_PRIM = "Lexer error. primary expected";
const std::string ERR_MSG_BRACKET = "Lexer error. ')' expected";

// Characters which can appear in expressions.
// Other characters are not allowed:
// if an expression contains other characters then the expression is invalid
// and must be considered as a regular string and is not to be parsed by the lexer
std::vector<char> Lexer::m_allowed_chars = {'*', '/', '-', '+', '(', ')',
            '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '.', ' '};

std::vector<std::string> Lexer::m_allowed_substrings;

bool Lexer::m_functions_initilized = false;

std::map<std::string,lexer_function_t> Lexer::m_functions;


Lexer::Lexer()
{
    if(!m_functions_initilized)
        lexer_functions_init();
}


Lexer::~Lexer()
{ }


double Lexer::Evaluate(std::string expression)
{
    expression += ';';
    EvaluateFunctions(expression);

    std::unique_ptr<std::istream> stream(new std::istringstream(expression.c_str()));
    m_current_instring = stream.get();

    GetToken();
    return Expression(false);
}

cad::command::Lexer::Token Lexer::GetToken()
{
    char ch;

    do {
		if(!m_current_instring->get(ch)) return current_token=END;
	} while (isspace(ch) && ch!='\n');

	switch(ch)
	{
        case 0:
        case ';':
            return END;
        case '*':
        case '/':
        case '-':
        case '+':
        case '(':
        case ')':
            return current_token=Token(ch);
        case '0': case '1': case '2': case '3': case '4':
        case '5': case '6': case '7': case '8': case '9':
        case '.':
            m_current_instring->putback(ch);
            *m_current_instring >> m_number_value;
            return current_token = NUMBER;

        default:
            throw LexerError(ERR_MSG_BAD_TOKEN + ch);
	}
}

double Lexer::Expression(bool get)
{
    double left = Term(get);
	for(;;)
		switch (current_token)
		{
            case Lexer::PLUS:
                left += Term(true);
                break;
            case Lexer::MINUS:
                left -= Term(true);
                break;
            default:
                return left;
		}
}

double Lexer::Term(bool get)
{
    double left = Prim(get);

	for (;;)
		switch (current_token)
		{
            case Lexer::MUL:
                left *= Prim(true);
                break;
            case Lexer::DIV:
                if (double d = Prim(true)) {
                    left /= d;
                    break;
                }
                throw LexerError(ERR_MSG_DIV_ZERO);
            default:
                return left;
		}
}

double Lexer::Prim(bool get)
{
    if (get) GetToken();

	switch (current_token)
	{
        case Lexer::NUMBER:
            GetToken();
            return m_number_value;
        case Lexer::MINUS:
            return -Prim(1);
        case Lexer::LP:
        {	double e = Expression(1);
            if (current_token != RP) throw LexerError(ERR_MSG_BRACKET);
            GetToken();
            return e;
        }
        case Lexer::END:
            return 1;
        default:
            throw LexerError(ERR_MSG_PRIM);
	}
}


bool Lexer::IsExpression(const std::string &expr) const
{
    std::string::size_type length = expr.size();
    std::string::size_type cursor = 0;

label_loop:
    while(cursor<length)
    {
        // Check functions (sub-strings)
        for(auto& func: m_functions)
        {
            std::string str = func.first;
            std::string::size_type sz = str.size();
            if(cursor + sz <= length)
                if(expr.substr(cursor, sz)==str)
                {
                    cursor += ++sz;
                    goto label_loop;
                }
        }

        // Check characters
        char symbol = expr.at(cursor++);
        auto found = std::find(m_allowed_chars.begin(), m_allowed_chars.end(), symbol);
        if(found==m_allowed_chars.end())
            return false;
    }
    return true;
}

void Lexer::EvaluateFunctions(std::string &expr)
{
    std::string::size_type sz = expr.size();
    std::string fn_name = "";
    lexer_function_t fn_ptr = nullptr;

    while(true)
    {
        //std::cout<<"\nEvaluating: "<<expr<<std::endl;
        std::string::size_type fn_pos = std::string::npos;
        size_t max_brackets = 0;
        for(auto fn: Lexer::m_functions)
        {
            std::string::size_type pos = expr.find(fn.first);
            if(pos != std::string::npos)
            {
                size_t brackets = 0;
                for(int c=0; c<pos; c++)
                    if(expr.at(c)=='(')
                       brackets++;

                //std::cout<<"\nIN: brackets:"<<brackets<<" max:"<<max_brackets<<std::endl;
                if(brackets>=max_brackets)
                {
                    max_brackets = brackets;
                    fn_pos = pos;
                    fn_name = fn.first;
                    fn_ptr = fn.second;
                    //std::cout<<fn_name<<" cbrackets:"<<max_brackets<<std::endl;
                }
            }
        }

        //std::cout<<"Is end:"<<(fn_pos==std::string::npos)<<std::endl;
        if(fn_pos==std::string::npos)
            break;

        if(expr.at(fn_pos+fn_name.size())!='(' || fn_pos+fn_name.size()>=expr.size())
            throw LexerError("Function error!");

        std::string::size_type cursor = fn_pos+fn_name.size();
        int bracket_counter = 1;
        while(bracket_counter!=0 && cursor<expr.size())
        {
            char symbol = expr.at(++cursor);
            if(symbol=='(')
                bracket_counter++;
            else if(symbol==')')
                bracket_counter--;

            //std::cout<<"Symbol: "<<symbol<<"  counter:"<<bracket_counter<<
            //"  cursor:"<<cursor<<std::endl;
        }

        ++cursor;
        std::string subexpr = expr.substr(fn_pos+fn_name.size(),
                                          cursor-(fn_pos+fn_name.size()));

        //std::cout<<"subexpr: "<<subexpr<<std::endl;
        double fn_arg = Evaluate(subexpr);
        double fn_result = fn_ptr(fn_arg);
        expr.replace(fn_pos, cursor - fn_pos, std::to_string(fn_result));
        //std::cout<<"Result:"<<fn_arg<<"  "<<fn_name<<" = "<<fn_result<<std::endl;
        //std::cout<<"Replaced:"<<expr<<std::endl;
    }

    return;
}

bool Lexer::AddFunction(std::string name, lexer_function_t fn)
{
    if(Lexer::m_functions.find(name)!=m_functions.end())
        return false;

    Lexer::m_functions.insert(std::pair<std::string, lexer_function_t>(name,fn));
    return true;
}
