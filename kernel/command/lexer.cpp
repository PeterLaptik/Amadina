#include "lexer.h"
#include "exceptions.h"
#include <iostream>
#include <memory>


const std::string ERR_MSG_BAD_TOKEN = "Lexer error. bad token:";
const std::string ERR_MSG_DIV_ZERO = "Lexer error. dividing by zero";
const std::string ERR_MSG_PRIM = "Lexer error. primary expected";
const std::string ERR_MSG_BRACKET = "Lexer error. ')' expected";


Lexer::Lexer()
    : instring(nullptr)
{ }


Lexer::~Lexer()
{ }


double Lexer::Evaluate(const std::string &expr)
{
    std::string expression = expr + ';';
    std::unique_ptr<std::istream> stream(new std::istringstream(expression.c_str()));

    instring = stream.get();
    GetToken();
    return Expression(false);
}

Lexer::Token Lexer::GetToken()
{
    char ch;

    do {
		if(!instring->get(ch)) return current_token=END;
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
            instring->putback(ch);
            *instring >> number_value;
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
        case Lexer::NUMBER:	    // floating point constant
            GetToken();
            return number_value;
        case Lexer::MINUS:		// unary minus
            return -Prim(1);
        case Lexer::LP:
        {	double e = Expression(1);
            if (current_token != RP) throw LexerError(ERR_MSG_BRACKET);
            GetToken();			 // eat ')'
            return e;
        }
        case Lexer::END:
            return 1;
        default:
            throw LexerError(ERR_MSG_PRIM);
	}
}

void Lexer::Skip()
{
	while (instring) {	// discard characters until newline or semicolon
				//       note: doesn't know the state of the parser
				//       so if the error was caused by a newline
				//       or a semicolon, we need to look for
				//       yet another terminator
		char ch;
		instring->get(ch);

		switch (ch) {
		case '\n':
		case ';':
        case 0:
			return;
		}
	}
}


