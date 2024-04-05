#include "model_tree.h"
#include "abstract_operation.h"
#include <typeinfo>


using cad::modeller::AbstractCanvas;
using cad::modeller::operations::AbstractOperation;


cad::modeller::ModelTree::~ModelTree()
{
	for (auto shape : m_shapes)
		delete shape;
}

void cad::modeller::ModelTree::AddItem(AbstractShape *item)
{
	m_shapes.push_back(item);
	item->AssignCanvas(m_canvas);
	item->Draw();
}

void cad::modeller::ModelTree::RemoveItem(AbstractShape *item)
{
	// Notify dependent operations about removed item. See description of a 'Purge'-method in AbstractOperation class.
	PurgeDependentOperations(item);

	auto it = std::remove(m_shapes.begin(), m_shapes.end(), item);
	m_shapes.erase(it, m_shapes.end());
	item->Hide();
	delete item;
}

void cad::modeller::ModelTree::RedrawItem(AbstractShape *item)
{
	item->SetVisible(true);
	item->Hide();
	item->Draw();
	UpdateDependentOperations(item);
}

void cad::modeller::ModelTree::HideItem(AbstractShape *item)
{
	item->Hide();
	item->SetVisible(false);
}

void cad::modeller::ModelTree::ShowItem(AbstractShape *item)
{
	item->Show();
	item->SetVisible(true);
}


void cad::modeller::ModelTree::RedrawTree()
{
	m_canvas->ClearAll();
	for (auto &obj : m_shapes)
		obj->Draw();
}

AbstractCanvas* cad::modeller::ModelTree::GetCanvas() const
{
	return m_canvas;
}

void cad::modeller::ModelTree::PurgeDependentOperations(AbstractShape *item) const
{
	for (auto &shape : m_shapes)
	{
		auto *op = dynamic_cast<AbstractOperation *>(shape);
		if (!op)
			continue;

		op->Purge(item);
	}
}

void cad::modeller::ModelTree::UpdateDependentOperations(AbstractShape *item) const
{
	for (auto &shape : m_shapes)
	{
		auto *op = dynamic_cast<AbstractOperation *>(shape);
		if (!op)
			continue;

		op->Update(item);
	}
}
