#ifndef OCCT_POINT_H
#define OCCT_POINT_H

#include "point.h"
#include "occt_object.h"
#include <AIS_Point.hxx>
#include <AIS_Shape.hxx>

#ifdef _WINDLL
	#define DLL_EXPORT __declspec(dllexport)
#else
	#define DLL_EXPORT
#endif

namespace cad::modeller::occt::shapes2D
{
	using cad::modeller::shapes2D::Point;

	class PointOcct : public Point, public OcctObject
	{
		public:
			using Point::Point;

			DLL_EXPORT ~PointOcct() override = default;

			DLL_EXPORT void AssignCanvas(AbstractCanvas *cnv) final;

			DLL_EXPORT void Draw() final;

			DLL_EXPORT void Hide() final;

			DLL_EXPORT void Show() final;

			DLL_EXPORT void Refresh() final;

			DLL_EXPORT void ExtractGeomCurves(std::vector<Handle(Geom_Curve)> &container) final;

			DLL_EXPORT void GetAisInteractiveObjects(std::vector<Handle(AIS_InteractiveObject)> &container) final;

		private:
			Handle(AIS_Shape) m_point = nullptr;
	};
}

#endif
