#ifndef OP_BOOL_OCCT_H
#define OP_BOOL_OCCT_H

#include "op_boolean.h"
#include "occt_object.h"
#include <AIS_Shape.hxx>

#ifdef _WINDLL
	#define DLL_EXPORT __declspec(dllexport)
#else
	#define DLL_EXPORT
#endif

namespace cad::modeller::occt::operations
{
	using cad::modeller::operations::OpBoolean;

	class OpBoolOcct : public OpBoolean, public OcctObject
	{
		public:
			OpBoolean::OpBoolean;

			~OpBoolOcct() override = default;

			DLL_EXPORT void AssignCanvas(AbstractCanvas *cnv) override;

			DLL_EXPORT bool IsValid() override;

			DLL_EXPORT void Hide() final;

			DLL_EXPORT void Show() final;

			DLL_EXPORT void Refresh() override;

			DLL_EXPORT void GetAisInteractiveObjects(std::vector<Handle(AIS_InteractiveObject)> &container) override;

			DLL_EXPORT void ExtractGeomCurves(std::vector<Handle(Geom_Curve)> &container) override;

		protected:
			Handle(AIS_Shape) m_body = nullptr;
	};
}

#endif

