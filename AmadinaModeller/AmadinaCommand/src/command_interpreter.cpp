#include "command_interpreter.h"
#include <sstream>
#include <algorithm>

#ifdef DEBUG_OUTPUT_AMADINA_COMMAND_INTERPRETER
    #include <iostream>
#endif

// Main token delimiter
// Commands and expressions should be delimited by this delimiter
const char DEFAULT_DELIMITER = ' ';

// Other allowed token delimiters
// The delimiters will be replaced with a main delimiter during string-expression processing
const char DELIMITERS[] {'\t'};

// Delimiters for lists of elements
// For example: 1, 2, 3 -- a list of three integers if the list delimiter is a comma
const char LIST_DELIMITER = ',';

// List braces
const char CH_START_LIST = '[';
const char CH_END_LIST = ']';

// String quotes: the quote character is not allowed inside strings
const char CH_STRING_QUOTES = '"';

// Characters which can appear in math expressions
// Other characters are not allowed:
// if an expression contains other characters, then the expression is invalid
// and must be considered as a regular string and is not to be parsed by the lexer
std::vector<char> cad::command::interpreter::CommandInterpreter::m_allowed_chars =
{'*', '/', '-', '+', '(', ')', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '.', ' '};


void cad::command::interpreter::CommandInterpreter::ParseExpression(std::string expr)
{
    m_string_tokens_container.clear();
    PurgeDelimiters(expr);

    ToLower(expr);

//
//    std::cout << "End   string: " << expr << std::endl;
    Tokenize(expr);
//    //std::cout << "Tokens: " << m_string_tokens_container.size() << std::endl;
//
//    auto lambda = [](Token token){
//        if(token.IsText()){
//            return "text    | ";
//        } else if(token.IsNumeric()){
//            return "numeric | ";
//        } else if(token.IsList()) {
//            return "list    | ";
//        } else if(token.IsString()) {
//            return "string  | ";
//        }
//        return "unknown |";
//    };
//
//    for(auto token: m_string_tokens_container)
//    {
//        std::cout << "Token: value = " << lambda(token) << token.GetStringValue() << std::endl;
//    }

}

// Splits expression into tokens using default-delimiter
void cad::command::interpreter::CommandInterpreter::Tokenize(const std::string &line)
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
            DebugOutput("Text: ", sstream.str());
            ProcessText(sstream);
            cursor++;
            continue;
        }
        // Process list (in-brackets value)
        if(ch==CH_START_LIST)
        {
            cursor++;
            //ProcessList(sstream, line, cursor);
            continue;
        }
        // Process string (in-quotes value)
        if(ch==CH_STRING_QUOTES)
        {
            cursor++;
            //ProcessString(sstream, line, cursor);
            continue;
        }
        sstream<<ch;
        cursor++;
    }
    // Flush remainder
    //ProcessText(sstream);
}

void cad::command::interpreter::CommandInterpreter::ProcessText(std::stringstream &sstream)
{
    std::istreambuf_iterator<char> eos;
    std::string value(std::istreambuf_iterator<char>(sstream), eos);
    if(value.empty())
        return;
    // Check number
    if(IsExpression(value))
    {
        //TryProcessNumberOrExpr(value);
        //m_string_tokens_container.push_back(Token(value, TOKEN_NUMERIC));
        return;
    }
//    // Check list
//    if(IsList(value))
//    {
//        try
//        {
//            ParseList(value);
//            m_string_tokens_container.push_back(Token(value, TOKEN_LIST));
//            return;
//        }
//        catch(const std::exception &e)
//        {
//            throw LexerError(ERR_MSG_LIST_ERROR + e.what());
//        }
//    }
//    // Otherwise text token
//    m_string_tokens_container.push_back(Token(value, TOKEN_TEXT));
}

// Checks if the expression contains only available characters,
// functions names, constants names
bool cad::command::interpreter::CommandInterpreter::IsExpression(const std::string &expr) const
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

// Replaces all allowed delimiters with space-delimiter.
// Following tokening will be performed for the default (space) delimiter only.
// In addition, delimiters before and after commas are removed
// For example: '1 , 1' translates into '1,1'
void cad::command::interpreter::CommandInterpreter::PurgeDelimiters(std::string &expr)
{
    DebugOutput("Start: ", expr);

    // Change all allowed delimiters to main delimiter (space by default)
    std::replace_if(std::begin(expr),std::end(expr),
                    [&](const char ch)
                    {
                        return std::find(std::begin(DELIMITERS), std::end(DELIMITERS), ch) != std::end(DELIMITERS);
                    },
                    DEFAULT_DELIMITER);

    // Trim spaces around list delimiters (commas by default)
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

    DebugOutput("Purged: ", expr);
}

// Forces all symbols to lower case (ignores symbols in quotes -- strings)
void cad::command::interpreter::CommandInterpreter::ToLower(std::string &expr)
{
    std::transform(expr.begin(), expr.end(), expr.begin(),
                   [](std::string::value_type ch)
                   {
                       static bool is_quoted = false;
                       is_quoted = ch == '"' ? !is_quoted : is_quoted;
                       return is_quoted ? ch : std::tolower(ch);
                   });

    DebugOutput("ToLower:", expr);
}


void cad::command::interpreter::CommandInterpreter::DebugOutput(const std::string &msg, const std::string &txt) const
{
    #ifdef DEBUG_OUTPUT_AMADINA_COMMAND_INTERPRETER
        std::cout << msg  << " : " << txt << std::endl;
    #endif
}

