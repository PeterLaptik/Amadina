#ifndef OCCT_CANVAS_H
#define OCCT_CANVAS_H

#include "abstract_canvas.h"
#include <AIS_InteractiveObject.hxx>

namespace cad
{
	namespace modeller
	{
		namespace occt
		{
			using cad::modeller::AbstractCanvas;

			///\brief A canvas interface for OCCT-implementation
			class OcctCanvas: public AbstractCanvas
			{
				public:
					OcctCanvas() = default;

					~OcctCanvas() override = default;

					///\brief Adds a new shape to show on screen
					virtual void AddShape(Handle(AIS_InteractiveObject) shape) = 0;

					///\brief Removes an existing shape from a screen
					//virtual void RemoveShape(Handle(AIS_InteractiveObject) shape) = 0;
			};
		}
	}
}

#endif