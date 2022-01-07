#include "arc.h"

Arc::Arc(const Point &center,
            const Point &start,
            const Point &end)
    : m_center(center),
    m_start(start),
    m_end(end)
{ }

Arc::~Arc()
{ }


void Arc::Draw(IAdapterDC &dc)
{
    dc.CadDrawArc(m_center, m_start, m_end);
}

Entity* Arc::Clone(void)
{
    return new Arc(m_center, m_start, m_end);
}
