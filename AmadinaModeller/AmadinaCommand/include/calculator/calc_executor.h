#ifndef INTERPRETER_EXECUTOR_H_INCLUDED
#define INTERPRETER_EXECUTOR_H_INCLUDED

#include <vector>

namespace cad::command::interpreter::grammar::calc::exec
{
    class Executor
    {
        public:
            explicit Executor(unsigned stackSize = 4096);
            ~Executor() = default;

            double top() const;
            void execute(std::vector<double> const& code);

        private:
            std::vector<double> stack;
            std::vector<double>::iterator stack_ptr;
    };
}

#endif // INTERPRETER_EXECUTOR_H_INCLUDED
