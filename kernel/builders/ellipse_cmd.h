#ifndef ELLIPSE_CMD_H_INCLUDED
#define ELLIPSE_CMD_H_INCLUDED

#include "../command/command.h"

class Ellipse;

class CmdEllipse: public Command
{
    public:
        CmdEllipse(Context *context = nullptr);
        virtual ~CmdEllipse();

        virtual void Run(void) final;
        virtual void Redraw(IAdapterDC &dc, double x, double y);
        virtual Command* Clone(Context *context) final;

    private:
        inline Ellipse BuildEllipse(void);

        bool p1_selected;
        bool p2_selected;
        Point pt1;
        Point pt2;
        Point pt3;
};

#endif // ELLIPSE_CMD_H_INCLUDED
