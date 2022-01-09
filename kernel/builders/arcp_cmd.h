#ifndef ARCP_CMD_H_INCLUDED
#define ARCP_CMD_H_INCLUDED

#include "../command/command.h"
#include "../entities/arc.h"

class CmdArcP: public Command
{
    public:
        CmdArcP(Context *context = nullptr);
        virtual ~CmdArcP();

        virtual void Run(void) final;
        virtual void Redraw(IAdapterDC &dc, double x, double y);
        virtual Command* Clone(Context *context) final;

    private:
        inline Arc BuildByThreePoints(const Point &p1,
                        const Point &p2, const Point &p3);

        bool has_pt_1;
        bool has_pt_2;
        Point pt_1;
        Point pt_2;
        Point pt_3;
};

#endif // ARCP_CMD_H_INCLUDED
