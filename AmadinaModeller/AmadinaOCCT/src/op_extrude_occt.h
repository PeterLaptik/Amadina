#ifndef OP_EXTRUDE_OCCT_INCLUDED_H
#define OP_EXTRUDE_OCCT_INCLUDED_H

#include "op_extrude.h"
#include "occt_object.h"
#include <AIS_Shape.hxx>

#ifdef _WINDLL
#define DLL_EXPORT __declspec(dllexport)
#else
#define DLL_EXPORT
#endif

namespace cad::model::occt::solid
{
    using cad::model::solid::OpExtrude;

    class OpExtrudeOcct : public OpExtrude, public OcctObject
    {
        public:
            using OpExtrude::OpExtrude;

            DLL_EXPORT ~OpExtrudeOcct() override = default;

            DLL_EXPORT void AssignCanvas(AbstractCanvas *cnv) final;

            DLL_EXPORT void DrawShape() final;

            DLL_EXPORT void RemoveShape() final;

            DLL_EXPORT bool IsValid() final;

            DLL_EXPORT void GetAisInteractiveObjects(std::vector<Handle(AIS_InteractiveObject)> &container) final;

            DLL_EXPORT void ExtractGeomCurves(std::vector<Handle(Geom_Curve)> &container) final;

        private:
            Handle(AIS_Shape) m_body = nullptr;
    };
}

#endif // OP_EXTRUDE_OCCT_INCLUDED_H