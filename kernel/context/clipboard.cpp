#include "clipboard.h"

ClipBoard::ClipBoard(Context *context)
    : m_context(context),
    m_base_point(0,0,0)
{ }


ClipBoard::~ClipBoard()
{
    Clear();
}

void ClipBoard::AddObjects(const std::vector<Entity*> &objects)
{
    Clear();
    for(auto i: objects)
        m_objects.push_back(i->Clone());
}

void ClipBoard::SetBasePoint(const Point &p)
{
    m_base_point = p;
}

const std::vector<Entity*>& ClipBoard::GetObjects() const
{
    return m_objects;
}

Point ClipBoard::GetBasePoint() const
{
    return m_base_point;
}

void ClipBoard::Clear()
{
    for(auto i: m_objects)
        delete i;
    m_objects.clear();
    m_base_point = Point(0,0,0);
}

bool ClipBoard::IsEmpty(void) const
{
    return m_objects.empty();
}
