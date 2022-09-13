#include "../include/interpreter.h"
#include <sstream>
#include <algorithm>
#include <iostream>

using Interpreter = cad::command::Interpreter;

// Main delimiter
const char DEFAULT_DELIMITER = ' ';
// Other allowed delimiters
// The delimiters will be replaced with main delimiter
// during string-expression processing
const char DELIMITERS[] {'\t'};
//
const char LIST_DELIMITER = ',';
//
const char CH_START_LIST = '[';
const char CH_END_LIST = ']';
//
const char CH_STRING_QUOTES = '"';
//
const std::string ERR_MSG_QUOTES = "Lexer error. expecting \"";
const std::string ERR_MSG_BRACKET = "Lexer error. expecting ]";
const std::string ERR_MSG_LIST_ERROR = "List parsing error. ";

Interpreter::Interpreter()
{ }

Interpreter::~Interpreter()
{ }

void Interpreter::ParseExpression(std::string expr)
{
    m_string_tokens_container.clear();
    std::cout << "Start string: " << expr << std::endl;
    PurgeDelimiters(expr);

    // Force all symbols to lower case
    std::transform(expr.begin(), expr.end(), expr.begin(),
                   [](std::string::value_type ch)
                   {
                       return std::tolower(ch);
                   });

    std::cout << "End   string: " << expr << std::endl;
    Tokenize(expr);
    //std::cout << "Tokens: " << m_string_tokens_container.size() << std::endl;

    auto lambda = [](Token token){
        if(token.IsText()){
            return "text    | ";
        } else if(token.IsNumeric()){
            return "numeric | ";
        } else if(token.IsList()) {
            return "list    | ";
        } else if(token.IsString()) {
            return "string  | ";
        }
        return "unknown |";
    };

    for(auto token: m_string_tokens_container)
    {
        std::cout << "Token: value = " << lambda(token) << token.GetStringValue() << std::endl;
    }

}

// Splits expression into tokens using default-delimiter
void Interpreter::Tokenize(const std::string &line)
{
    std::stringstream sstream;
    std::string::size_type sz = line.size();
    std::string::size_type cursor = 0;
    while(cursor<sz)
    {
        char ch = line.at(cursor);
        // Process delimited symbolic value
        if(ch==DEFAULT_DELIMITER)
        {
            ProcessText(sstream);
            cursor++;
            continue;
        }
        // Process list (in-brackets value)
        if(ch==CH_START_LIST)
        {
            cursor++;
            ProcessList(sstream, line, cursor);
            continue;
        }
        // Process string (in-quotes value)
        if(ch==CH_STRING_QUOTES)
        {
            cursor++;
            ProcessString(sstream, line, cursor);
            continue;
        }
        sstream<<ch;
        cursor++;
    }
    // Flush remainder
    ProcessText(sstream);
}

void Interpreter::ProcessText(std::stringstream &sstream)
{
    std::istreambuf_iterator<char> eos;
    std::string value(std::istreambuf_iterator<char>(sstream), eos);
    if(value.empty())
        return;
    // Check number
    if(m_lexer.IsExpression(value))
    {
        TryProcessNumberOrExpr(value);
        m_string_tokens_container.push_back(Token(value, TOKEN_NUMERIC));
        return;
    }
    // Check list
    if(IsList(value))
    {
        try
        {
            ParseList(value);
            m_string_tokens_container.push_back(Token(value, TOKEN_LIST));
            return;
        }
        catch(const std::exception &e)
        {
            throw LexerError(ERR_MSG_LIST_ERROR + e.what());
        }
    }
    // Otherwise text token
    m_string_tokens_container.push_back(Token(value, TOKEN_TEXT));
}

void Interpreter::TryProcessNumberOrExpr(std::string &value)
{
    double num_value = m_lexer.Evaluate(value);
    value = std::to_string(num_value);
}

void Interpreter::ProcessList(std::stringstream &sstream, const std::string &line,
                             std::string::size_type &cursor)
{
    std::string::size_type sz = line.size();
    while(cursor<sz)
    {
        char ch = line.at(cursor);
        if(ch==CH_END_LIST)
        {
            std::istreambuf_iterator<char> eos;
            std::string value(std::istreambuf_iterator<char>(sstream), eos);
            ParseList(value);
            m_string_tokens_container.push_back(Token(value, TOKEN_LIST));
            cursor++;
            return;
        }
        sstream<<ch;
        cursor++;
    }
    if(cursor==sz)
        throw LexerError(ERR_MSG_BRACKET);
}

void Interpreter::ParseList(std::string &lst)
{
    std::string lst_result;
    std::string list_element;
    std::stringstream sstream(lst);

    while(getline(sstream, list_element, LIST_DELIMITER))
    {
        if(list_element.size()!=0)
        {
            double result = m_lexer.Evaluate(list_element);
            lst_result += std::to_string(result);
            lst_result += LIST_DELIMITER;
            //std::cout << "List element: " << result << std::endl;
        }
    }
    lst = lst_result.erase(lst_result.size()-1);
}

void Interpreter::ProcessString(std::stringstream &sstream, const std::string &line,
                             std::string::size_type &cursor)
{
    std::string::size_type sz = line.size();
    while(cursor<sz)
    {
        char ch = line.at(cursor);
        if(ch==CH_STRING_QUOTES)
        {
            std::istreambuf_iterator<char> eos;
            std::string value(std::istreambuf_iterator<char>(sstream), eos);
            m_string_tokens_container.push_back(Token(value, TOKEN_STRING));
            cursor++;
            return;
        }
        sstream<<ch;
        cursor++;
    }
    if(cursor==sz)
        throw LexerError(ERR_MSG_QUOTES);
}

bool Interpreter::IsList(const std::string &token)
{
    return token.find(LIST_DELIMITER)!=std::string::npos;
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
    while(pos<expr.size() && (pos = expr.find(LIST_DELIMITER, pos))!=std::string::npos)
    {
        // right trim
        pos++;
        while(pos<expr.size() && expr.at(pos)==DEFAULT_DELIMITER)
            expr.erase(pos++, 1);
        // left trim
        pos -= 3;
        while(pos<expr.size() && pos>=0 && expr.at(pos)==DEFAULT_DELIMITER)
            expr.erase(pos--, 1);
        // return to the last position
        pos += 3;
    }
}

