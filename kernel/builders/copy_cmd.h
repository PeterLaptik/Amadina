#ifndef COPY_CMD_H_INCLUDED
#define COPY_CMD_H_INCLUDED

#include "../command/command.h"

class CmdCopy: public Command
{
    public:
        CmdCopy(Context *context = nullptr);
        virtual ~CmdCopy();

        virtual void Run(void);
        virtual Command* Clone(Context *context);
        virtual bool IsMultiCommand(void);

    private:
        std::vector<Entity*> selection;
        std::vector<Entity*> clones;
};

#endif // COPY_CMD_H_INCLUDED
