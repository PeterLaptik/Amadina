#include "../include/lexer.h"
#include <sstream>
#include <memory>
#include <iostream>
#include <algorithm>
#include <cctype>

using Lexer = cad::command::Lexer;
using lexer_function_t = cad::command::lexer_function_t;

// Exceptions messages
const std::string ERR_MSG_BAD_TOKEN = "Lexer error. bad token: ";
const std::string ERR_MSG_DIV_ZERO = "Lexer error. dividing by zero.";
const std::string ERR_MSG_PRIM = "Lexer error. primary expected.";
const std::string ERR_MSG_BRACKET = "Lexer error. ')' expected.";
const std::string ERR_MSG_EXPR_ERROR = "Expression error.";
const std::string ERR_MSG_FUNCTION_ERROR = "Function error!";

const int MAX_RECURSIVE_DEBT = 10;

// Characters which can appear in expressions.
// Other characters are not allowed:
// if an expression contains other characters, then the expression is invalid
// and must be considered as a regular string and is not to be parsed by the lexer
std::vector<char> Lexer::m_allowed_chars = {'*', '/', '-', '+', '(', ')',
            '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '.', ' '};

bool Lexer::m_functions_initilized = false;

std::map<std::string,lexer_function_t> Lexer::m_functions;

std::vector<std::string> Lexer::m_functions_names;

std::map<std::string,double> Lexer::m_constants;

std::vector<std::string> Lexer::m_constants_names;


Lexer::Lexer()
{
    if(!m_functions_initilized)
        lexer_functions_init();
}


Lexer::~Lexer()
{ }


double Lexer::Evaluate(std::string expression)
{
    double result = 0;
    try
    {
        expression += ';';
        ToLowerCase(expression);
        m_call_counter = 0;
        EvaluateFunctions(expression);
        ReplaceConstants(expression);
        std::unique_ptr<std::istream> stream(new std::istringstream(expression.c_str()));
        m_current_instring = stream.get();

        GetToken();
        result = Expression(false);
    }
    catch (const std::exception &e)
    {
        throw LexerError(std::string("In expression '") + expression + "'. " + e.what());
    }
    return result;
}

cad::command::Lexer::Token Lexer::GetToken()
{
    char ch;

    m_call_counter++;
    if(m_call_counter>MAX_RECURSIVE_DEBT)
        throw LexerError(ERR_MSG_EXPR_ERROR);

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
            m_call_counter--;
            return current_token=Token(ch);
        case '0': case '1': case '2': case '3': case '4':
        case '5': case '6': case '7': case '8': case '9':
        case '.':
            m_current_instring->putback(ch);
            *m_current_instring >> m_number_value;
            m_call_counter--;
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

// Checks if the expression contains only available characters,
// functions names, constants names
bool Lexer::IsExpression(const std::string &expr) const
{
    std::string::size_type length = expr.size();
    std::string::size_type cursor = 0;

label_loop:
    while(cursor<length)
    {
        // Check functions (sub-strings)
        for(auto& func: m_functions_names)
        {
            std::string::size_type sz = func.size();
            if(cursor + sz <= length)
                if(expr.substr(cursor, sz)==func)
                {
                    cursor += ++sz;
                    goto label_loop;
                }
        }
        // Check constants (sub-strings)
        for(auto& cnst: m_constants_names)
        {
            std::string::size_type sz = cnst.size();
            if(cursor + sz <= length)
                if(expr.substr(cursor, sz)==cnst)
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
        std::string::size_type fn_pos = std::string::npos;
        size_t max_brackets = 0;
        for(auto fn_str: Lexer::m_functions_names)
        {
            std::string::size_type pos = expr.find(fn_str);
            if(pos != std::string::npos)
            {
                size_t brackets = 0;
                for(int c=0; c<pos; c++)
                    if(expr.at(c)=='(')
                       brackets++;

                if(brackets>=max_brackets)
                {
                    max_brackets = brackets;
                    fn_pos = pos;
                    auto fn_pair = Lexer::m_functions.find(fn_str);
                    fn_name = fn_pair->first;
                    fn_ptr = fn_pair->second;
                }
            }
        }

        if(fn_pos==std::string::npos)
            break;

        if(expr.at(fn_pos+fn_name.size())!='(' || fn_pos+fn_name.size()>=expr.size())
            throw LexerError(ERR_MSG_FUNCTION_ERROR);

        std::string::size_type cursor = fn_pos+fn_name.size();
        int bracket_counter = 1;
        while(bracket_counter!=0 && cursor<expr.size())
        {
            char symbol = expr.at(++cursor);
            if(symbol=='(')
                bracket_counter++;
            else if(symbol==')')
                bracket_counter--;
        }

        ++cursor;
        std::string subexpr = expr.substr(fn_pos+fn_name.size(),
                                          cursor-(fn_pos+fn_name.size()));
        // Recursive call
        double fn_arg = Evaluate(subexpr);
        double fn_result = fn_ptr(fn_arg);
        expr.replace(fn_pos, cursor - fn_pos, std::to_string(fn_result));
    }
}

void Lexer::ReplaceConstants(std::string &expr)
{
    for(auto const_name: Lexer::m_constants_names)
    {
        std::string::size_type c_pos = expr.find(const_name);
        while(c_pos!=std::string::npos)
        {
            std::string substitution = std::to_string(Lexer::m_constants.find(const_name)->second);
            expr.replace(c_pos, const_name.size(), substitution);
            c_pos = expr.find(const_name);
        }
    }
}

bool Lexer::AddConstant(std::string name, double value)
{
    ToLowerCase(name);
    if(Lexer::m_constants.find(name)!=m_constants.end() || name.empty())
        return false;

    m_constants_names.push_back(name);
    Lexer::m_constants.insert(std::pair<std::string, double>(name,value));
    std::sort(m_constants_names.begin(), m_constants_names.end(),
              [](const std::string &name_1, const std::string &name_2)
              {
                  return name_1.size()<name_2.size();
              }
    );
    return true;
}

bool Lexer::AddFunction(std::string name, lexer_function_t fn)
{
    ToLowerCase(name);
    if(Lexer::m_functions.find(name)!=m_functions.end() || name.empty())
        return false;

    m_functions_names.push_back(name);
    Lexer::m_functions.insert(std::pair<std::string, lexer_function_t>(name,fn));
    std::sort(m_functions_names.begin(), m_functions_names.end(),
              [](const std::string &name_1, const std::string &name_2)
              {
                  return name_1.size()<name_2.size();
              }
    );
    return true;
}

void Lexer::UseDegreesForAngles(bool use_degrees)
{
    lexer_set_use_degree_units(use_degrees);
}

void Lexer::ToLowerCase(std::string &str)
{
    std::transform(str.begin(), str.end(), str.begin(),
                   [](std::string::value_type ch)
                   {
                       return std::tolower(ch);
                   });
}
