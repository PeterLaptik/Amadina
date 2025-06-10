#ifndef BASE_CALCULATOR_H_INCLUDED
#define BASE_CALCULATOR_H_INCLUDED

#include <string>
#include <map>

namespace cad::command::interpreter::grammar::calc {

    class BaseCalculator
    {
        public:
            BaseCalculator(std::map<std::string, double> &vars_list,
                std::map<std::string, double> &const_list);

            double EvaluateMathExpression(const std::string &math_expr) const;

        private:
            std::map<std::string, double> &m_variables;
            std::map<std::string, double> &m_constants;
    };

}

#endif