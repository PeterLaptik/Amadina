#ifndef CIRCLEBUILDER_H_INCLUDED
#define CIRCLEBUILDER_H_INCLUDED

#include "abstractbuilder.h"

class CircleBuilder: public AbstractBuilder
{
    public:
        CircleBuilder();
        virtual ~CircleBuilder();

        virtual bool AppendPoint(const Point &pt);

        virtual void Redraw(IAdapterDC &dc, double x, double y);

        virtual Entity* Create(void);
};

#endif // CIRCLEBUILDER_H_INCLUDED
