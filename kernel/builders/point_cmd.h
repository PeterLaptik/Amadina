#ifndef POINT_CMD_H_INCLUDED
#define POINT_CMD_H_INCLUDED

#include "../command/command.h"

class CmdPoint final: public Command
{
    public:
        CmdPoint(Context *context = nullptr);
        virtual ~CmdPoint();

        virtual void Run(void) final;
        virtual Command* Clone(Context *context = nullptr) final;

    private:

};

#endif // POINT_CMD_H_INCLUDED
