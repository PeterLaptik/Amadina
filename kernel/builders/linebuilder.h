#ifndef LINEBUILDER_H_INCLUDED
#define LINEBUILDER_H_INCLUDED

#include "abstractbuilder.h"

class LineBuilder: public AbstractBuilder
{
    public:
        LineBuilder();
        virtual ~LineBuilder();

        virtual bool AppendPoint(const Point &pt);

        virtual void Redraw(IAdapterDC &dc,  double x, double y);

        virtual Entity* Create(void);

        virtual bool IsMultiBuild(void) const;
};

#endif // LINEBUILDER_H_INCLUDED
