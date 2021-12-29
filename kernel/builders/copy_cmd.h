#ifndef COPY_CMD_H_INCLUDED
#define COPY_CMD_H_INCLUDED

#include "../command/command.h"
#include "../entities/point.h"

class CmdCopy: public Command
{
    public:
        CmdCopy(Context *context = nullptr);
        virtual ~CmdCopy();

        virtual void Run(void);
        virtual Command* Clone(Context *context);
        virtual bool IsMultiCommand(void);

    private:
        Point m_base_point;
        std::vector<Entity*> m_selection;
};

#endif // COPY_CMD_H_INCLUDED
