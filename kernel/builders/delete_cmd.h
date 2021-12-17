#ifndef DELETE_CMD_H_INCLUDED
#define DELETE_CMD_H_INCLUDED

#include "../command/command.h"

class CmdDelete final: public Command
{
    public:
        CmdDelete(Context *context = nullptr);
        virtual ~CmdDelete();

        virtual void Run(void) final;
        virtual Command* Clone(Context *context) final;

    private:
        std::vector<Entity*> selection;
};

#endif // DELETE_CMD_H_INCLUDED
