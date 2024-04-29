#include "abstract_operation.h"

bool cad::modeller::operations::AbstractOperation::DoesOperationDependOnShape(AbstractShape *shape, const std::vector<AbstractShape*> &dep_shapes)
{
	auto it = std::find_if(dep_shapes.begin(), dep_shapes.end(),
		[shape](auto obj) {
			return obj == shape;
		});

	return it != dep_shapes.end();
}

bool cad::modeller::operations::AbstractOperation::DoesOperationDependOnSubShapes(AbstractShape *shape, const std::vector<AbstractShape*> &dep_shapes)
{
	std::vector<AbstractShape *> sub_shapes;
	shape->GetSubObjects(sub_shapes);

	for (auto sub_shape : sub_shapes)
	{
		auto its = std::find_if(dep_shapes.begin(), dep_shapes.end(),
			[sub_shape](auto obj) {
				return obj == sub_shape;
			});

		if (its != dep_shapes.end())
			return true;
	}

	return false;
}
