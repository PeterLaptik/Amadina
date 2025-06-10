#include "abstract_shape.h"

void cad::model::AbstractShape::Draw()
{
    m_is_visible = true;
    DrawShape();
}

void cad::model::AbstractShape::Remove()
{
    m_is_visible = false;
    RemoveShape();
}

void cad::model::AbstractShape::Refresh()
{
    if (m_is_visible)
    {
        RemoveShape();
        DrawShape();
    }
}

void cad::model::AbstractShape::GetSubObjects(std::vector<AbstractShape *> &container)
{
    // no sub-objects by default
    // should be overriden for composite shapes
}

bool cad::model::AbstractShape::IsVisible() const
{
    return m_is_visible;
}

void cad::model::AbstractShape::SetHandled(bool is_handled)
{
    m_is_handled_by_operation = is_handled;
}

bool cad::model::AbstractShape::IsHandled() const
{
    return m_is_handled_by_operation;
}

void cad::model::AbstractShape::SetVisible(bool visible)
{
    m_is_visible = visible;
}
