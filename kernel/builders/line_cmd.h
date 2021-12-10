#ifndef LINE_CMD_H_INCLUDED
#define LINE_CMD_H_INCLUDED

#include "../command/command.h"
#include "../entities/point.h"


class CmdLine final: public Command
{
    public:
        CmdLine(Context *context = nullptr);
        virtual ~CmdLine();

        virtual void Run(void) final;
        virtual void Redraw(IAdapterDC &dc, double x, double y);
        virtual Command* Clone(Context *context) final;

    private:
        bool m_pt1_picked;
        Point pt1;
        Point pt2;
};

#endif // LINE_CMD_H_INCLUDED
