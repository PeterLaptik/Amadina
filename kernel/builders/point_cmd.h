#ifndef POINT_CMD_H_INCLUDED
#define POINT_CMD_H_INCLUDED

#include "../command/command.h"
#include "../api/exports.h"

class DLL_EXPORT CmdPoint final: public Command
{
    public:
        CmdPoint(Context *context = nullptr);
        virtual ~CmdPoint();

        virtual void Run(void) final;
        virtual Command* Clone(Context *context) final;
        virtual bool IsMultiCommand(void) const;

    private:

};

#endif // POINT_CMD_H_INCLUDED
