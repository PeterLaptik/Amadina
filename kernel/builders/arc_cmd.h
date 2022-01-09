#ifndef ARC_CMD_H_INCLUDED
#define ARC_CMD_H_INCLUDED

#include "../command/command.h"

class CmdArc final: public Command
{
    public:
        CmdArc(Context *context = nullptr);
        virtual ~CmdArc();

        virtual void Run(void) final;
        virtual void Redraw(IAdapterDC &dc, double x, double y);
        virtual Command* Clone(Context *context) final;

    private:
        // Moves end point to on-arc position
        // (end point is not on actual radius)
        inline void Normalize(void);

        bool m_pt_center_picked;
        bool m_pt_1_picked;
        Point pt_center;
        Point pt_start;
        Point pt_end;
};

#endif // ARC_CMD_H_INCLUDED
