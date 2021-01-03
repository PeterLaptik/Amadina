#ifndef POINTBUILDER_H_INCLUDED
#define POINTBUILDER_H_INCLUDED

#include "abstractbuilder.h"

class PointBuilder: public AbstractBuilder
{
    public:
        PointBuilder();
        virtual ~PointBuilder();

        virtual bool AppendPoint(const Point &pt);

        virtual void Redraw(IAdapterDC &dc, double x, double y);

        virtual Entity* Create(void);

        virtual bool IsMultiBuild(void) const;
};

#endif // POINTBUILDER_H_INCLUDED
