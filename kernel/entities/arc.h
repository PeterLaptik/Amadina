#ifndef ARC_H_INCLUDED
#define ARC_H_INCLUDED

#include "entity.h"
#include "point.h"

class Arc: public Entity
{
    public:
        Arc(const Point &center,
            const Point &start,
            const Point &end);

        virtual ~Arc();
        virtual void Draw(IAdapterDC &dc);
        virtual Entity* Clone(void);

    private:
        Point m_center;
        Point m_start;
        Point m_end;

};

#endif // ARC_H_INCLUDED
