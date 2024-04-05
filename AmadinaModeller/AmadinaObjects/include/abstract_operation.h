#ifndef ABSTRACT_OPERATION_H
#define ABSTRACT_OPERATION_H

#include "abstract_shape.h"


#ifdef _WINDLL
	#define DLL_EXPORT __declspec(dllexport)
#else
	#define DLL_EXPORT
#endif


namespace cad::modeller::operations
{
	///\brief Represents basic operation and its result (extrusion, swipe, boolean operations, etc.)
	class DLL_EXPORT AbstractOperation : public AbstractShape
	{
		public:
			AbstractOperation() = default;

			~AbstractOperation() override = default;

			/// Checks wether objects required by the operation exist and valid.
			/// For example, deleting of an object the operation depends on invalidates the operation.
			/// Results of invalid operations should not be shown on a canvas.
			virtual bool IsValid(void) = 0;

			/// The method is called on every deleting of existing objects.
			/// The method should check the operation state if 'removed_shape' belongs to the operation,
			/// remove junk links and pointers, validate the operation.
			virtual void Purge(AbstractShape *removed_shape) = 0;

			/// The method is called on every changing of existing objects.
			/// The method should check and update the operation state if 'updated_shape' belongs to the operation.
			virtual void Update(AbstractShape *updated_shape) = 0;

			/// Utility method: checks whether an operation depends on a shape.
			///\param shape -- shape to check for dependency
			///\param dep_shapes -- list of shapes, used by the operation
			///\return true if the opertion uses the shape, otherwise false
			static bool DoesOperationDependOnShape(AbstractShape *shape, const std::vector<AbstractShape*> &dep_shapes);
			
			/// Utility method: checks whether an operation depends on a shape sub-shapes.
			///\param shape -- shape to check subshapes for dependencies
			///\param dep_shapes -- list of shapes, used by the operation
			///\return true if the opertion uses the shape sub-shapes, otherwise false
			static bool DoesOperationDependOnSubShapes(AbstractShape *shape, const std::vector<AbstractShape*> &dep_shapes);
	};
}

#endif
