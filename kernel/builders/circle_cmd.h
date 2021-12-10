#ifndef CIRCLE_CMD_H_INCLUDED
#define CIRCLE_CMD_H_INCLUDED

#include "../command/command.h"
#include "../entities/point.h"

class CmdCircle final: public Command
{
    public:
        CmdCircle(Context *context = nullptr);
        virtual ~CmdCircle();

        virtual void Run(void) final;
        virtual void Redraw(IAdapterDC &dc, double x, double y);
        virtual Command* Clone(Context *context) final;

    private:
        bool m_pt_picked;
        Point pt1;
        Point pt2;
};

#endif // CIRCLE_CMD_H_INCLUDED
