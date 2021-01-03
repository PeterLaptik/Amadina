#ifndef SQUAREBUILDER_H_INCLUDED
#define SQUAREBUILDER_H_INCLUDED

#include "abstractbuilder.h"

class SquareBuilderByCenter: public AbstractBuilder
{
    public:
        SquareBuilderByCenter();
        virtual ~SquareBuilderByCenter();

        virtual bool AppendPoint(const Point &pt);

        virtual void Redraw(IAdapterDC &dc, double x, double y);

        virtual Entity* Create(void);
};


class SquareBuilderByPoints: public AbstractBuilder
{
    public:
        SquareBuilderByPoints();
        virtual ~SquareBuilderByPoints();

        virtual bool AppendPoint(const Point &pt);

        virtual void Redraw(IAdapterDC &dc, double x, double y);

        virtual Entity* Create(void);
};

#endif // SQUAREBUILDER_H_INCLUDED
