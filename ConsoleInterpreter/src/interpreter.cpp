#include "interpreter.h"
#include <sstream>
#include <algorithm>
#include <iostream>

// Main delimiter
static const char DELIMITER = ' ';
// Other allowed delimiters
// The delimiters will be replaced with main delimiter
// during string-expression processing
const char DELIMITERS[] {'\t'};

cad::command::Interpreter::Interpreter()
{ }

cad::command::Interpreter::~Interpreter()
{ }

void cad::command::Interpreter::ParseExpression(std::string expr)
{
    std::cout << "Start string: " << expr << std::endl;
    PurgeDelimiters(expr);
    std::cout << "End   string: " << expr << std::endl;
}

void cad::command::Interpreter::TrimSpacesAfterCommas(std::string &expr)
{

}

void cad::command::Interpreter::ReadSubExpressions(std::string &line,
                                      std::vector<std::string> &tokens)
{
    std::string token;
    std::stringstream sstream(line);

    while(getline(sstream, token, DELIMITER))
    {
        if(token.size()>0)
            tokens.push_back(token);
    }

}

// Replace all allowed delimiters with space-delimiter
// Following tokenizing will be performed for the space-delimiter
void cad::command::Interpreter::PurgeDelimiters(std::string &expr)
{
    for(int i=0; i<sizeof(DELIMITERS)/sizeof(char); i++)
        std::replace(std::begin(expr),std::end(expr), DELIMITERS[i], ' ');
}


