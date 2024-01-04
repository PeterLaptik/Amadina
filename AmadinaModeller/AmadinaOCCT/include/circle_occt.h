#ifndef OCCT_CIRCLE_H
#define OCCT_CIRCLE_H

#include "circle.h"
#include "occt_object_container.h"
#include <AIS_Circle.hxx>

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
				using cad::modeller::shapes2D::Circle;

				class CircleOcct : public Circle, public OcctObjectContainer
				{
					public:
						using Circle::Circle;

						DLL_EXPORT ~CircleOcct() override = default;

						DLL_EXPORT void Draw(AbstractCanvas &cnv) final;

						DLL_EXPORT void ExtractGeomCurves(std::vector<Handle(Geom_Curve)> &container) final;

						DLL_EXPORT void GetAisInteractiveObjects(std::vector<Handle(AIS_InteractiveObject)> &container) final;

					private:
						Handle(AIS_Circle) m_circle = nullptr;
				};
			}
		}
	}
}

#endif
