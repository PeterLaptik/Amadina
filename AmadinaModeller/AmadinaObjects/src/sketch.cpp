#include "sketch.h"
#include<algorithm>

using cad::model::geom::DirectionVector;

cad::model::flat::Sketch::Sketch(const std::string &name)
    : m_name(name)
{ }

cad::model::flat::Sketch::~Sketch()
{
    for (auto shape : m_shapes)
        delete shape;
}

void cad::model::flat::Sketch::AppendObject(AbstractShape *shape)
{
    m_shapes.push_back(shape);
}

void cad::model::flat::Sketch::RemoveObject(AbstractShape *shape)
{
    for (auto &obj : m_shapes)
    {
        if (obj == shape)
        {
            delete obj;
            obj = nullptr;
        }
    }

    m_shapes.erase(std::remove(m_shapes.begin(), m_shapes.end(), shape), m_shapes.end());
}

void cad::model::flat::Sketch::SetDirectionVector(const DirectionVector &vector)
{
    m_vector = vector;
}

DirectionVector cad::model::flat::Sketch::GetDirectionVector() const
{
    return m_vector;
}

void cad::model::flat::Sketch::GetSubObjects(std::vector<AbstractShape *> &container)
{
    for (auto &entity : m_shapes)
    {
        container.push_back(entity);
        entity->GetSubObjects(container);
    }
}


