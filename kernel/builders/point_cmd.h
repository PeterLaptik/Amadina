#ifndef POINT_CMD_H_INCLUDED
#define POINT_CMD_H_INCLUDED

#include "../command/command.h"

class CmdPoint: public Command
{
    public:
        CmdPoint();
        virtual ~CmdPoint();

//        virtual void Execute(void) = 0;
//        virtual Command Clone(void) = 0;

    private:

};

#endif // POINT_CMD_H_INCLUDED
