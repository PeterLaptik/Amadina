#ifndef OCCT_SKETCH_H
#define OCCT_SKETCH_H

#include "sketch.h"
#include "occt_object.h"
#include "direction_vector.h"
#include <vector>
#include<string>

#ifdef _WINDLL
	#define DLL_EXPORT __declspec(dllexport)
#else
	#define DLL_EXPORT
#endif

namespace cad::modeller::occt
{
	using cad::modeller::shapes2D::Sketch;
	using cad::modeller::geometry::DirectionVector;

	///\brief Sketch draft is assembled from 2D elements (e.g. points, lines, circles etc.)
	class SketchOcct : public Sketch, public OcctObject
	{
		public:
			DLL_EXPORT explicit SketchOcct(const std::string &name);

			DLL_EXPORT ~SketchOcct() override = default;

			DLL_EXPORT void AssignCanvas(AbstractCanvas *cnv) final;

			DLL_EXPORT void Draw() final;

			DLL_EXPORT void Hide() final;

			DLL_EXPORT void Show() final;

			DLL_EXPORT void Refresh() final;

			DLL_EXPORT void SetDirectionVector(const DirectionVector &vector);

			DLL_EXPORT DirectionVector GetDirectionVector() const;

			DLL_EXPORT void GetAisInteractiveObjects(std::vector<Handle(AIS_InteractiveObject)> &container) final;

			DLL_EXPORT void ExtractGeomCurves(std::vector<Handle(Geom_Curve)> &container) final;

		private:
			std::string m_name;
			DirectionVector m_vector;
	};
}

#endif // OCCT_SKETCH_H

