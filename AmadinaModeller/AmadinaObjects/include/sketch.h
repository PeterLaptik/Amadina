#ifndef ABSTRACT_SKETCH_H
#define ABSTRACT_SKETCH_H

#include "abstract_shape.h"
#include <vector>

#ifdef _WINDLL
	#define DLL_EXPORT __declspec(dllexport)
#else
	#define DLL_EXPORT
#endif

namespace cad::modeller::shapes2D
{
	///\brief Represents a flat sketch: object which contains a set of 2D shapes
	class Sketch : public AbstractShape
	{
	public:
		DLL_EXPORT Sketch() = default;

		DLL_EXPORT ~Sketch() override;

		DLL_EXPORT virtual void AppendObject(AbstractShape *shape);

		DLL_EXPORT virtual void RemoveObject(AbstractShape *shape);

		DLL_EXPORT void GetSubObjects(std::vector<AbstractShape *> &container) override;

	protected:
		std::vector<AbstractShape *> m_shapes;
	};
}

#endif
