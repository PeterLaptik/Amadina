#include "../include/interpreter.h"
#include <sstream>
#include <algorithm>
#include <iostream>

using Interpreter = cad::command::Interpreter;

// Main delimiter
static const char DEFAULT_DELIMITER = ' ';
// Other allowed delimiters
// The delimiters will be replaced with main delimiter
// during string-expression processing
const char DELIMITERS[] {'\t'};


Interpreter::Interpreter()
{ }

Interpreter::~Interpreter()
{ }

void Interpreter::ParseExpression(std::string expr)
{
    m_string_tokens_container.clear();
    std::cout << "Start string: " << expr << std::endl;
    PurgeDelimiters(expr);
    std::cout << "End   string: " << expr << std::endl;
    Tokenize(expr);
    std::cout << "Tokens: " << m_string_tokens_container.size() << std::endl;
    for(auto token: m_string_tokens_container)
    {
//        if(IsList(token))
//            ParseList(token);

        std::cout << token << " is list:" << IsList(token) << std::endl;
    }

}

// Splits expression into tokens using default-delimiter
void Interpreter::Tokenize(const std::string &line)
{
    const char START_LIST = '[';
    const char END_LIST = ']';

    std::stringstream sstream;
    std::string::size_type sz = line.size();
    std::string::size_type cursor = 0;
    while(cursor<sz)
    {
        char ch = line.at(cursor);
        sstream<<ch;
        std::cout<<ch;
        cursor++;
    }
    std::cout<<std::endl<<"srtream: "<<sstream.str()<<std::endl;
    m_string_tokens_container.push_back(sstream.str());
}

bool Interpreter::IsList(const std::string &token)
{
    std::cout << "Checking:" << token << " is list:" << token.find(',') << std::endl;
    return token.find(',')!=std::string::npos;
}

void Interpreter::ParseList(const std::string &list_str)
{
    std::cout << "List: " << list_str << std::endl;

    std::string list_element;
    std::stringstream sstream(list_str);

    while(getline(sstream, list_element, ','))
    {
        if(list_element.size()!=0)
        {
            double result = m_lexer.Evaluate(list_element);
            std::cout << "List element: " << result << std::endl;
        }
    }
}

// Replaces all allowed delimiters with space-delimiter.
// Following tokenizing will be performed for the default (space) delimiter only.
// In addition, delimiters before and after commas are removed
// For example: '1 , 1' translates into '1,1'
void Interpreter::PurgeDelimiters(std::string &expr)
{
    // Change all allowed delimiters to main delimiter (space by default)
    for(int i=0; i<sizeof(DELIMITERS)/sizeof(char); i++)
        std::replace(std::begin(expr),std::end(expr), DELIMITERS[i], DEFAULT_DELIMITER);

    // Trim spaces around commas
    std::string::size_type pos = 0;
    while(pos<expr.size() && (pos = expr.find(',', pos))!=std::string::npos)
    {
        // right trim
        pos++;
        while(pos<expr.size() && expr.at(pos)==DEFAULT_DELIMITER)
            expr.erase(pos++, 1);
        // left trim
        pos -= 3;
        while(pos<expr.size() && expr.at(pos)==DEFAULT_DELIMITER)
            expr.erase(pos--, 1);
        // return to the last position
        pos += 3;
    }

    // Trim spaces inside brackets
}




