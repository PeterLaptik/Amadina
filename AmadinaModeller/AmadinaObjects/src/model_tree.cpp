#include "model_tree.h"
#include "abstract_operation.h"
#include <typeinfo>


using cad::model::AbstractCanvas;
using cad::model::solid::AbstractOperation;


cad::model::ModelTree::ModelTree(AbstractCanvas *canvas)
    :m_canvas(canvas)
{ }

cad::model::ModelTree::~ModelTree()
{
    // Suppress any visual refreshing on a modeller closing to avoid broken pointers errors
    for (auto shape : m_shapes)
        shape->AssignCanvas(nullptr);

    for (auto it = m_shapes.rbegin(); it != m_shapes.rend(); ++it)
        delete *it;
}

void cad::model::ModelTree::AddItem(AbstractShape *item)
{
    m_shapes.push_back(item);
    item->AssignCanvas(m_canvas);
    item->Draw();
}

void cad::model::ModelTree::RemoveItem(AbstractShape *item)
{
    // Notify dependent operations about removed item. See description of a 'Purge'-method in AbstractOperation class.
    PurgeDependentOperations(item);

    auto it = std::remove(m_shapes.begin(), m_shapes.end(), item);
    m_shapes.erase(it, m_shapes.end());
    item->Remove();
    delete item;
}

void cad::model::ModelTree::HideItem(AbstractShape *item)
{
    item->Remove();
}

void cad::model::ModelTree::ShowItem(AbstractShape *item)
{
    item->Draw();
}


void cad::model::ModelTree::RedrawTree()
{
    for (auto &obj : m_shapes)
        obj->Refresh();
}

AbstractCanvas *cad::model::ModelTree::GetCanvas() const
{
    return m_canvas;
}

void cad::model::ModelTree::PurgeDependentOperations(AbstractShape *item) const
{
    for (auto &shape : m_shapes)
    {
        auto *op = dynamic_cast<AbstractOperation *>(shape);
        if (!op)
            continue;

        op->Purge(item);
    }
}

