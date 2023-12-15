#include "op_bool_fuse.h"

using AbstractShape = cad::modeller::AbstractShape;

cad::modeller::operations::OpBoolFuse::OpBoolFuse(std::vector<AbstractShape *> &&shapes)
	: m_initial_shapes(std::move(shapes))
{ }

const std::vector<AbstractShape *>& cad::modeller::operations::OpBoolFuse::GetShapes() const
{
	return m_initial_shapes;
}
