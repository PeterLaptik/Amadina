#ifndef CIRCLEP_CMD_H_INCLUDED
#define CIRCLEP_CMD_H_INCLUDED

#include "../command/command.h"
#include "../entities/point.h"

class Circle;

class CmdCircleP final: public Command
{
    public:
        CmdCircleP(Context *context = nullptr);
        virtual ~CmdCircleP();

        virtual void Run(void) final;
        virtual void Redraw(IAdapterDC &dc, double x, double y);
        virtual Command* Clone(Context *context) final;

    private:
        inline Circle BuildCircle(double x, double y);

        bool m_pt_1_picked;
        bool m_pt_2_picked;
        Point pt1;
        Point pt2;
        Point pt3;
};

#endif // CIRCLEP_CMD_H_INCLUDED
