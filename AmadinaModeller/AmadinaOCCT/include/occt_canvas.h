#ifndef OCCT_CANVAS_H
#define OCCT_CANVAS_H

#include "abstract_canvas.h"
#include <AIS_InteractiveObject.hxx>

namespace cad::modeller::occt
{
	using cad::modeller::AbstractCanvas;

	///\brief A canvas interface for OCCT-implementation
	class OcctCanvas : public AbstractCanvas
	{
		public:
			OcctCanvas() = default;

			~OcctCanvas() override = default;

			virtual void AddShape(Handle(AIS_InteractiveObject) shape) = 0;

			virtual void RemoveShape(Handle(AIS_InteractiveObject) shape) = 0;

			virtual bool ContainsShapes(const std::vector<Handle(AIS_InteractiveObject)> &objects) = 0;
	};
}

#endif