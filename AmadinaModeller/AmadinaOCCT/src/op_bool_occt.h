#ifndef OP_BOOL_OCCT_INCLUDED_H
#define OP_BOOL_OCCT_INCLUDED_H

#include "op_boolean.h"
#include "occt_object.h"
#include <AIS_Shape.hxx>

#ifdef _WINDLL
#define DLL_EXPORT __declspec(dllexport)
#else
#define DLL_EXPORT
#endif

namespace cad::model::occt::solid
{
    using cad::model::solid::OpBoolean;

    class OpBoolOcct : public OpBoolean, public OcctObject
    {
        public:
            using OpBoolean::OpBoolean;

            DLL_EXPORT ~OpBoolOcct() override = default;

            DLL_EXPORT void AssignCanvas(AbstractCanvas *cnv) override;

            DLL_EXPORT bool IsValid() override;

            DLL_EXPORT void GetAisInteractiveObjects(std::vector<Handle(AIS_InteractiveObject)> &container) override;

            DLL_EXPORT void ExtractGeomCurves(std::vector<Handle(Geom_Curve)> &container) override;

        protected:
            Handle(AIS_Shape) m_body = nullptr;
    };
}

#endif // OP_BOOL_OCCT_INCLUDED_H

