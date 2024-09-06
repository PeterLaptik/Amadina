#ifndef COMMAND_TRANSFORMER_H_INCLUDED
#define COMMAND_TRANSFORMER_H_INCLUDED

#include "command_ast.h"
#include "command_token.h"
#include "grammars/calculator/base_calculator.h"
#include <map>

namespace cad::command::interpreter::grammar::commands::ast
{
    class CommandTransformer
    {
        public:
            CommandTransformer(std::map<std::string, double> &vars_list,
                std::map<std::string, double> &const_list);

            CommandToken operator()(const Text &token) const; // Common case: regular text
            CommandToken operator()(const String &str) const; // Quoted string
            CommandToken operator()(const List &list)  const; // Comma delimited values in brackets

        private:
            cad::command::interpreter::grammar::calc::BaseCalculator m_calc;
    };
}

#endif // !COMMAND_TRANSFORMER_H_INCLUDED

