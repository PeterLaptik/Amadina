#ifndef ABSTRACT_SKETCH_H
#define ABSTRACT_SKETCH_H

#include "abstract_shape.h"
#include <vector>

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
			class Sketch: public AbstractShape
			{
				public:
					DLL_EXPORT Sketch() = default;

					DLL_EXPORT ~Sketch() override;

					DLL_EXPORT void AppendObject(AbstractShape *shape);

					DLL_EXPORT void RemoveObject(AbstractShape *shape);

					DLL_EXPORT void GetShapes(std::vector<AbstractShape *> &receiver) const;

				private:
					std::vector<AbstractShape *> m_shapes;
			};
		}
	}
}

#endif
