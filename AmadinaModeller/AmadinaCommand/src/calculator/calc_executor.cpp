#include "calculator/calc_executor.h"
#include "calculator/calc_operations.h"
#include "parser_exception.h"

const char *const MSG_BAD_OPERATION = "Unknown operation. ";


cad::command::interpreter::grammar::calc::exec::Executor::Executor(unsigned stackSize)
              : stack(stackSize), stack_ptr(stack.begin())
{ }

double cad::command::interpreter::grammar::calc::exec::Executor::Top() const
{
    return stack_ptr[-1];
}

void cad::command::interpreter::grammar::calc::exec::Executor::Execute(const std::vector<double> &code)
{
    auto pc = code.begin();
    stack_ptr = stack.begin();

    while (pc != code.end())
    {
        switch (static_cast<int>(*pc++))
        {
            case op_neg:
                stack_ptr[-1] = -stack_ptr[-1];
                break;

            case op_add:
                --stack_ptr;
                stack_ptr[-1] += stack_ptr[0];
                break;

            case op_sub:
                --stack_ptr;
                stack_ptr[-1] -= stack_ptr[0];
                break;

            case op_mul:
                --stack_ptr;
                stack_ptr[-1] *= stack_ptr[0];
                break;

            case op_div:
                --stack_ptr;
                stack_ptr[-1] /= stack_ptr[0];
                break;

            case op_num:
                *stack_ptr++ = *pc++;
                break;

            default:
                throw ParserException(MSG_BAD_OPERATION + '(' + static_cast<int>(*pc++) + ')');
        }
    }
}
