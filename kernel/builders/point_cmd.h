#ifndef POINT_CMD_H_INCLUDED
#define POINT_CMD_H_INCLUDED

#include "../command/command.h"

class CmdPoint final: public Command
{
    public:
        CmdPoint(Context *context);
        virtual ~CmdPoint();

        virtual void Execute(void) final;
        virtual Command* Clone(void) final;

    private:

};

#endif // POINT_CMD_H_INCLUDED
