#ifndef VAR_ASSIGNER_H_INCLUDED
#define VAR_ASSIGNER_H_INCLUDED

#include "grammars/variables/var_ast.h"
#include "grammars/calculator/base_calculator.h"
#include <string>
#include <map>

namespace cad::command::interpreter::grammar::variables
{
    class VarAssigner
    {
        public:
            VarAssigner(std::map<std::string, double> &vars_list,
                std::map<std::string, double> &const_list);

            void AssignVar(std::string expression);

        private:
            void PutVariable(const std::string &var_name, double var_value) const;
            void PutConstant(const std::string &const_name, double const_value) const;
            bool DoesConstantExist(const std::string &constant_name) const;

            cad::command::interpreter::grammar::calc::BaseCalculator m_calc;
            std::map<std::string, double> &m_variables;
            std::map<std::string, double> &m_constants;
    };
}

#endif // !VAR_ASSIGNER_H_INCLUDED




