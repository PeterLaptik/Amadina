#ifndef OCCT_POINT_H
#define OCCT_POINT_H

#include "point.h"
#include "sketch_object.h"
#include <AIS_Point.hxx>

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
				using cad::modeller::shapes2D::Point;

				class PointOcct : public Point, public SketchObject
				{
					public:
						using Point::Point;

						DLL_EXPORT ~PointOcct() override = default;

						DLL_EXPORT void Draw(AbstractCanvas &cnv) final;

						DLL_EXPORT void GetAisInteractiveObjects(std::vector<Handle(Geom_TrimmedCurve)> &container) final;

					private:
						Handle(AIS_Point) m_point = nullptr;
				};
			}
		}
	}
}

#endif
