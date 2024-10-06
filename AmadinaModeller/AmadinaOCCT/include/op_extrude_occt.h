#ifndef OP_EXTRUDE_OCCT_H
#define OP_EXTRUDE_OCCT_H

#include "op_extrude.h"
#include "occt_object.h"
#include <AIS_Shape.hxx>

#ifdef _WINDLL
	#define DLL_EXPORT __declspec(dllexport)
#else
	#define DLL_EXPORT
#endif

namespace cad::modeller::occt::operations
{
	using cad::modeller::operations::OpExtrude;

	class OpExtrudeOcct : public OpExtrude, public OcctObject
	{
		public:
			using OpExtrude::OpExtrude;

			DLL_EXPORT ~OpExtrudeOcct() override = default;

			DLL_EXPORT void AssignCanvas(AbstractCanvas *cnv) final;

			DLL_EXPORT void Draw() final;

			DLL_EXPORT void Hide() final;

			DLL_EXPORT void Show() final;

			DLL_EXPORT void Refresh() final;

			DLL_EXPORT bool IsValid() final;

			DLL_EXPORT void GetAisInteractiveObjects(std::vector<Handle(AIS_InteractiveObject)> &container) final;

			DLL_EXPORT void ExtractGeomCurves(std::vector<Handle(Geom_Curve)> &container) final;

		private:
			Handle(AIS_Shape) m_body = nullptr;
	};
}

#endif