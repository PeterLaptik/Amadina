#include "op_bool_fuse.h"

using cad::modeller::AbstractShape;
//using cad::modeller::ShapeIterator;

void cad::modeller::operations::OpBoolFuse::AddShape(AbstractShape *shape)
{
	// TODO check if exists
	m_initial_shapes.push_back(shape);
}

/*
ShapeIterator cad::modeller::operations::OpBoolFuse::GetShapes() const
{
	return ShapeIterator(m_initial_shapes);
}
*/