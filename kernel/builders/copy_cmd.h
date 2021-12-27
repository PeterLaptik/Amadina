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
        virtual void Redraw(IAdapterDC &dc, double x, double y);
        virtual Command* Clone(Context *context);
        virtual bool IsMultiCommand(void);

    private:
        bool m_is_showing;
        Point m_base_point;
        Point m_insert_point;
        std::vector<Entity*> m_selection;
        std::vector<Entity*> m_clones;
};

#endif // COPY_CMD_H_INCLUDED
