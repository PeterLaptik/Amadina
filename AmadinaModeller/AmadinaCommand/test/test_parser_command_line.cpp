#include "command_parser.h"
#include "command_arguments.h"
#include "grammars/variables/var_assigner.h"
#include "grammars/calculator/base_calculator.h"
#include "parser_exception.h"
#include "grammars/variables/var_grammar.h"
#include "grammars/calculator/calc_grammar.h"
#include "grammars/calculator/calc_evaluator.h"
#include "grammars/command_line/command_grammar.h"
#include "assert.h"
#include <boost/spirit/home/x3.hpp>
#include <iostream>


std::string token_to_string(const cad::command::interpreter::CommandToken &tk);


std::vector<std::string> test_line_commands = {
    "LINE [0,0] [10, 10.5, 15.1] \"Sketch_1\" xFlag",
    "   Circle [10,10+5, 15.4]  \"Sketch_2\" r15   ",
    "bOx (1.5*2/3+cos(rad(0)))",
    "command x (15+4)",
    " command x (15+4) ",
    "  command x (15+4)  ",
};

void check_command_line_expressions(void)
{
    using cad::command::interpreter::CommandToken;
    using cad::command::interpreter::CommandArguments;
    
    std::cout << "Command line parser test: " << std::endl;
    cad::command::interpreter::CommandParser parser;

    for (auto &expr : test_line_commands)
    {

        std::cout << "Command line: '" << expr << "'\t";
        bool res = parser.ParseCommand(expr);
        if (!res)
            throw std::exception(parser.GetResultMessage().c_str());

        // Has tokens?
        bool is_empty = parser.IsEmpty();
        assert(!is_empty);

        std::cout << "cmd: '" << parser.GetCommand() << "'\t";

        CommandArguments args = parser.GetArguments();
        size_t tokens_number = args.GetSize();
        for (int i = 0; i < tokens_number; i++)
        {
            const CommandToken &tk = args.GetArg(i);
            std::cout << token_to_string(tk) << "\t";

            // List size check
            if (tk.IsList())
                assert(tk.GetListSize());

            // Text forced lowercase characters check
            if (tk.IsText())
            {
                std::string lower_txt;
                std::transform(tk.GetStringValue().begin(), tk.GetStringValue().end(), std::back_inserter(lower_txt),
                    [](auto ch) {
                        return std::tolower(ch);
                    });

                assert(lower_txt == tk.GetStringValue());
            }
        }
        std::cout << std::endl;
    }
}

std::string token_to_string(const cad::command::interpreter::CommandToken &tk)
{
    std::string result;
    if (tk.IsText())
    {
        result += ("txt: " + tk.GetStringValue());
    }

    if (tk.IsString())
    {
        result += ("str: " + tk.GetStringValue());
    }

    if (tk.IsNumeric())
    {
        result += ("num: " + std::to_string(tk.GetNumericValue()));
    }

    if (tk.IsList())
    {
        result += "[";
        size_t list_size = tk.GetListSize();
        for (int i = 0; i < list_size; i++)
        {
            result += std::to_string(tk.GetListValue(i));
            result += (i != list_size - 1 ? ", " : "");
        }
        result += "]";
    }

    return result;
}
