#ifndef OCCT_CANVAS_INCLUDED_H
#define OCCT_CANVAS_INCLUDED_H

#include "abstract_canvas.h"
#include <AIS_InteractiveObject.hxx>

namespace cad::model::occt
{
    using cad::model::AbstractCanvas;

    ///\brief A common canvas interface for OCCT-implementation. \n
    /// Displays objects at screen (panel) and provides interactive functions. \n
    /// Uses OCCT context (AIS_InteractiveContext) to display objects.
    ///\see wxOccPanel implementation
    class OcctCanvas : public AbstractCanvas
    {
        public:
            OcctCanvas() = default;

            ~OcctCanvas() override = default;

            /// Displays object at AIS_InteractiveContext (visualization)
            ///\param item item to display 
            virtual void AddShape(Handle(AIS_InteractiveObject) item) = 0;

            /// Removes object from AIS_InteractiveContext
            ///\param item item to remove / hide 
            virtual void RemoveShape(Handle(AIS_InteractiveObject) item) = 0;

            /// Checks whether all objects from a list are displayed at AIS_InteractiveContext
            ///\param objects objects list to check
            ///\return true if all objects from the list are displayed at a context
            virtual bool ContainsShapes(const std::vector<Handle(AIS_InteractiveObject)> &objects) = 0;
    };
}

#endif // OCCT_CANVAS_INCLUDED_H