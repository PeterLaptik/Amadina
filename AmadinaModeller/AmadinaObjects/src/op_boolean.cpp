#include "op_boolean.h"
#include <algorithm>
#include <iterator>


using cad::modeller::AbstractShape;


cad::modeller::operations::OpBoolean::~OpBoolean()
{
	for (auto shape : m_initial_shapes)
	{
		shape->SetHandled(false);
		shape->SetVisible(true);
	}
}

void cad::modeller::operations::OpBoolean::AddShape(AbstractShape *shape)
{
	if (shape->GetIsHandled())
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

void cad::modeller::operations::OpBoolean::RemoveShape(AbstractShape *shape)
{
	m_initial_shapes.erase(std::remove(m_initial_shapes.begin(), m_initial_shapes.end(), shape), m_initial_shapes.end());
	shape->SetHandled(false);
	shape->SetVisible(true);
	Refresh();
}

 void cad::modeller::operations::OpBoolean::Purge(AbstractShape *shape)
{
	 bool shape_dep = AbstractOperation::DoesOperationDependOnShape(shape, m_initial_shapes);
	 bool sub_shapes_dep = AbstractOperation::DoesOperationDependOnSubShapes(shape, m_initial_shapes);

	 if (shape_dep)
	 {
		 m_initial_shapes.erase(std::remove(m_initial_shapes.begin(), m_initial_shapes.end(), shape), m_initial_shapes.end());
		 shape->SetHandled(false);
		 shape->SetVisible(true);
	 }

	 if (shape_dep || sub_shapes_dep)
		 Refresh();
}

 void cad::modeller::operations::OpBoolean::Update(AbstractShape *updated_shape)
 {
	 bool shape_dep = AbstractOperation::DoesOperationDependOnShape(updated_shape, m_initial_shapes);
	 bool sub_shapes_dep = AbstractOperation::DoesOperationDependOnSubShapes(updated_shape, m_initial_shapes);
	 if (shape_dep || sub_shapes_dep)
		 Refresh();
 }

 void cad::modeller::operations::OpBoolean::GetSubObjects(std::vector<AbstractShape *> &container)
 {
	 for (auto obj : m_initial_shapes)
	 {
		 container.push_back(obj);
		 obj->GetSubObjects(container);
	 }
 }

void cad::modeller::operations::OpBoolean::GetShapes(std::vector<AbstractShape *> &container) const
{
	std::copy(m_initial_shapes.begin(), m_initial_shapes.end(), std::back_inserter(container));
}

int cad::modeller::operations::OpBoolean::GetShapesNumber() const
{
	return static_cast<int>(m_initial_shapes.size());
}

