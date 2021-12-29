#ifndef PASTE_CMD_H_INCLUDED
#define PASTE_CMD_H_INCLUDED

#include "../command/command.h"

class CmdPaste: public Command
{
    public:
        CmdPaste(Context *context = nullptr);
        virtual ~CmdPaste();

        virtual void Run(void);
        virtual void Redraw(IAdapterDC &dc, double x, double y);
        virtual Command* Clone(Context *context);
        virtual bool IsMultiCommand(void);

    private:
        Point m_base_point;
        Point m_insert_point;
        std::vector<Entity*> m_clones;
};

#endif // PASTE_CMD_H_INCLUDED
