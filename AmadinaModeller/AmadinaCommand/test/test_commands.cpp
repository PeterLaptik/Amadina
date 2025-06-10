#include "base_command.h"
#include "command_parser.h"
#include "model_tree.h"
#include "application_context.h"
#include "sheet_context.h"
#include "abstract_canvas.h"
#include <assert.h>
#include <iostream>
#include <sstream>

#include "create_sketch.h"

void output_args_info(const std::string &cmd_name, cad::command::interpreter::CommandArguments &args);
std::string argument_to_string(const cad::command::CommandToken&);

void init_commands(cad::app::ApplicationContext &actx);

std::vector<std::string> commands_to_test = {
    "sketch [0, 0, 0] [0, 1, 0] Sketch_number_1"
};

void test_command()
{
    cad::app::ApplicationContext actx;
    cad::app::AbstractCanvas cnv;
    cad::model::ModelTree tree{&cnv};
    cad::app::SheetContext ctx{&actx};
    ctx.SetModelTree(&tree);

    init_commands(actx);

    using cad::command::interpreter::CommandToken;
    cad::command::interpreter::CommandParser parser;

    for (std::string command : commands_to_test)
    {
        bool res = parser.ParseCommand(command);
        assert(res);

        std::string cmd_name = parser.GetCommand();
        cad::command::interpreter::CommandArguments arguments = parser.GetArguments();
        output_args_info(cmd_name, arguments);

        BaseCommand *cmd = actx.GetCommand(cmd_name);
        assert(cmd);

        cmd->Execute(&ctx, arguments);

        delete cmd;
    }
}

void output_args_info(const std::string &cmd_name, cad::command::interpreter::CommandArguments &args)
{
    std::cout << "Command: " << cmd_name << std::endl;
    size_t arg_num = args.GetSize();
    for (size_t i = 0; i < arg_num; i++)
    {
        cad::command::CommandToken token = args.GetArg(i);
        std::cout << "Argument " << i << ": " << argument_to_string(token) << std::endl;
    }
}

std::string argument_to_string(const cad::command::CommandToken &tk)
{
    if (tk.IsString() || tk.IsText()) {
        return tk.GetStringValue();
    }
    
    std::stringstream sstr;
    if (tk.IsList()) {
        size_t max = tk.GetListSize();
        sstr << "{";
        for (size_t i = 0; i < max; i++)
        {
            sstr << tk.GetListValue(i);
            if (i < max - 1)
                sstr << ", ";
            else
                sstr << "}";
        }
        return sstr.str();
    }

    if (tk.IsNumeric())
    {
        sstr << tk.GetNumericValue();
        return sstr.str();
    }

    return "???";
}

void init_commands(cad::app::ApplicationContext &actx)
{
    actx.AddCommand("Sketch", new cad::command::CreateSketch());
}