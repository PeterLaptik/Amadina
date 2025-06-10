#include "op_boolean.h"
#include <algorithm>
#include <iterator>

using cad::model::AbstractShape;

cad::model::solid::OpBoolean::~OpBoolean()
{
    for (auto shape : m_initial_shapes)
    {
        shape->SetHandled(false);
        shape->Draw();
    }
}

void cad::model::solid::OpBoolean::AddShape(AbstractShape *shape)
{
    if (shape->IsHandled())
        return; // the shape is used by another operation

    auto it = std::find_if(m_initial_shapes.begin(), m_initial_shapes.end(),
        [=](auto obj) {
            return obj == shape;
        });

    if (it != m_initial_shapes.end())
        return; // the shape already exists in the list

    m_initial_shapes.push_back(shape);
    shape->SetHandled(true);
    Refresh();
}

void cad::model::solid::OpBoolean::RemoveShape(AbstractShape *shape)
{
    m_initial_shapes.erase(std::remove(m_initial_shapes.begin(), m_initial_shapes.end(), shape), m_initial_shapes.end());
    shape->SetHandled(false);
    shape->Draw();
    Refresh();
}

void cad::model::solid::OpBoolean::Purge(AbstractShape *removing_shape)
{
    auto its = std::find_if(m_initial_shapes.begin(), m_initial_shapes.end(),
        [removing_shape](auto obj) {
            return obj == removing_shape;
        });

    bool has_direct_dependency = its != m_initial_shapes.end();

    if (has_direct_dependency)
    {
        m_initial_shapes.erase(std::remove(m_initial_shapes.begin(), m_initial_shapes.end(), removing_shape), m_initial_shapes.end());
        removing_shape->SetHandled(false);
        Refresh();
    }
}

void cad::model::solid::OpBoolean::Update(AbstractShape *updated_shape)
{
    bool has_dependencies = DoesDependOn(updated_shape);
    if (has_dependencies)
        Refresh();
}

void cad::model::solid::OpBoolean::GetSubObjects(std::vector<AbstractShape *> &container)
{
    for (auto obj : m_initial_shapes)
    {
        container.push_back(obj);
        obj->GetSubObjects(container);
    }
}

void cad::model::solid::OpBoolean::GetShapes(std::vector<AbstractShape *> &container) const
{
    std::copy(m_initial_shapes.begin(), m_initial_shapes.end(), std::back_inserter(container));
}

int cad::model::solid::OpBoolean::GetShapesNumber() const
{
    return static_cast<int>(m_initial_shapes.size());
}

bool cad::model::solid::OpBoolean::DoesDependOn(AbstractShape *shape)
{
    std::vector<AbstractShape *> sub_shapes;
    sub_shapes.push_back(shape);
    shape->GetSubObjects(sub_shapes);

    for (auto sub_shape : sub_shapes)
    {
        auto its = std::find_if(m_initial_shapes.begin(), m_initial_shapes.end(),
            [sub_shape](auto obj) {
                return obj == sub_shape;
            });

        if (its != m_initial_shapes.end())
            return true;
    }

    return false;
}

