#include "../include/lexer.h"
#include <sstream>
#include <memory>

const std::string ERR_MSG_BAD_TOKEN = "Lexer error. bad token:";
const std::string ERR_MSG_DIV_ZERO = "Lexer error. dividing by zero";
const std::string ERR_MSG_PRIM = "Lexer error. primary expected";
const std::string ERR_MSG_BRACKET = "Lexer error. ')' expected";

cad::command::Lexer::Lexer()
{ }


cad::command::Lexer::~Lexer()
{ }


double cad::command::Lexer::Evaluate(const std::string &expr)
{
    std::string expression = expr + ';';
    std::unique_ptr<std::istream> stream(new std::istringstream(expression.c_str()));

    m_instring_pt = stream.get();
    GetToken();
    return Expression(false);
}

cad::command::Lexer::Token cad::command::Lexer::GetToken()
{
    char ch;

    do {
		if(!m_instring_pt->get(ch)) return current_token=END;
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
            m_instring_pt->putback(ch);
            *m_instring_pt >> number_value;
            return current_token = NUMBER;

        default:
            throw LexerError(ERR_MSG_BAD_TOKEN + ch);
	}
}

double cad::command::Lexer::Expression(bool get)
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

double cad::command::Lexer::Term(bool get)
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

double cad::command::Lexer::Prim(bool get)
{
    if (get) GetToken();

	switch (current_token)
	{
        case Lexer::NUMBER:
            GetToken();
            return number_value;
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
