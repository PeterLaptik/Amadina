#ifndef ABSTRACT_SHAPE_H
#define ABSTRACT_SHAPE_H

#include "abstract_canvas.h"
#include <string>

#ifdef _WINDLL
	#define DLL_EXPORT __declspec(dllexport)
#else
	#define DLL_EXPORT
#endif

namespace cad
{
	namespace modeller
	{
		///\brief Abstract shape represents any type of 2D or 3D entity which can be shown
		class DLL_EXPORT AbstractShape
		{
			public:
				AbstractShape() = default;

				virtual ~AbstractShape() = default;

				///\brief Draws object at a canvas-widget.
				/// Concrete shape implementations can receive implementation dependent canvas sub-types.
				/// Use downcasting of the canvas link to use it properly.
				/// See OCCT shapes implementations.
				virtual void Draw(AbstractCanvas &cnv) = 0;
		};
	}
}

#endif
