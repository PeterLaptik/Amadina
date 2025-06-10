#ifndef ABSTRACT_OPERATION_INCLUDED_H
#define ABSTRACT_OPERATION_INCLUDED_H

#include "abstract_shape.h"


#ifdef _WINDLL
#define DLL_EXPORT __declspec(dllexport)
#else
#define DLL_EXPORT
#endif


namespace cad::model::solid
{
    ///\brief Represents basic operation and its result (extrusion, swipe, boolean operations, etc.) \n
    /// Each operation keeps pointers to the objects depends on (see methods Purge and Update).
    class AbstractOperation : public AbstractShape
    {
        public:
            DLL_EXPORT AbstractOperation() = default;

            DLL_EXPORT ~AbstractOperation() override = default;

            /// Checks whether the operation is valid and can be evaluated (objects required by the operation are set and valid). \n
            /// Results of invalid operations should not be shown on a canvas. \n
            /// TODO describe example
            ///\return whether the operation can be evaluated and shown (true/false)
            DLL_EXPORT virtual bool IsValid(void) = 0;

            /// The method is called for all operarions if any object is being deleted. \n
            /// The method should recheck the operation state: if 'removed_shape' belongs to the operation. \n
            /// Removes junk links and broken pointers, validates the operation. Keeps an operation consistent. \n
            /// TODO describe example
            ///\param removed_shape shape which is being removed from model
            DLL_EXPORT virtual void Purge(AbstractShape *removing_shape) = 0;

            /// The method is called on every changing of existing objects. \n
            /// The method should check and update / rebuild the operation and its state if 'updated_shape' belongs to the operation. \n
            /// TODO describe example
            ///\param updated_shape - shape which has been updated
            DLL_EXPORT virtual void Update(AbstractShape *updated_shape) = 0;

            /// Checks whether an operation depends on a shape (handle a shape). \n
            /// Note: implementation should check shape itself as well as sub-shapes. \n
            /// TODO describe example
            ///\see Any operation implementation
            ///\param shape	- shape to check for dependency
            ///\param dep_shapes - list of shapes, used by the operation
            ///\return true if the opertion uses the shape, otherwise false
            DLL_EXPORT virtual bool DoesDependOn(AbstractShape *shape) = 0;
    };
}

#endif // ABSTRACT_OPERATION_INCLUDED_H
