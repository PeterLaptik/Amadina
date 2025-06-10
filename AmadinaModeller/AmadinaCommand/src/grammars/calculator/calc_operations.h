#ifndef INTERPRETER_OPERATIONS_H_INCLUDED
#define INTERPRETER_OPERATIONS_H_INCLUDED

namespace cad::command::interpreter::grammar::calc
{
    enum OperationCode
    {
        op_neg,     //  negate the top stack entry
        op_add,     //  add top two stack entries
        op_sub,     //  subtract top two stack entries
        op_mul,     //  multiply top two stack entries
        op_div,     //  divide top two stack entries
        op_num,     //  push number into the stack
        op_fnu,     //  unary function call
        op_fnb      //  binary function call
    };
}

#endif // INTERPRETER_OPERATIONS_H_INCLUDED
