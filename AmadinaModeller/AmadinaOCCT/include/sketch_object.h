#ifndef SKETCH_SHAPE_H
#define SKETCH_SHAPE_H

#include <vector>
#include <Geom_TrimmedCurve.hxx>

#ifdef _WINDLL
	#define DLL_EXPORT __declspec(dllexport)
#else
	#define DLL_EXPORT
#endif

namespace cad
{
	namespace modeller
	{
		namespace occt
		{
			namespace shapes2D
			{
				class DLL_EXPORT SketchObject
				{
					public:
						virtual ~SketchObject() = default;

						virtual void GetAisInteractiveObjects(std::vector<Handle(Geom_TrimmedCurve)> &container) = 0;
				};
			}
		}
	}
}

#endif // !SKETCH_SHAPE_H

