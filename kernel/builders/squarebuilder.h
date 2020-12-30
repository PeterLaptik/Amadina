#ifndef SQUAREBUILDER_H_INCLUDED
#define SQUAREBUILDER_H_INCLUDED

#include "abstractbuilder.h"

class SquareBuilder: public AbstractBuilder
{
    public:
        SquareBuilder();
        virtual ~SquareBuilder();

        virtual bool AppendPoint(const Point &pt);

        virtual void Redraw(IAdapterDC &dc, double x, double y);

        virtual Entity* Create(void);
};

#endif // SQUAREBUILDER_H_INCLUDED
