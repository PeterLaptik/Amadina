#ifndef ABSTRACT_SKETCH_H
#define ABSTRACT_SKETCH_H

#include "abstract_shape.h"

#ifdef _WINDLL
	#define DLL_EXPORT __declspec(dllexport)
#else
	#define DLL_EXPORT
#endif

namespace cad
{
	namespace modeller
	{
		namespace shapes2D
		{
			///\brief Represents sketch: object wich contains a flat set of 2D shapes
			class DLL_EXPORT Sketch: public AbstractShape
			{
				public:
				Sketch() = default;

				~Sketch() override = default;

				virtual void AppendObject(AbstractShape *shape) = 0;
			};
		}
	}
}

#endif
