#ifndef OCCT_CIRCLE_INCLUDED_H
#define OCCT_CIRCLE_INCLUDED_H

#include "circle.h"
#include "occt_object.h"
#include <AIS_Circle.hxx>

#ifdef _WINDLL
#define DLL_EXPORT __declspec(dllexport)
#else
#define DLL_EXPORT
#endif

namespace cad::model::occt::flat
{
    using cad::model::flat::Circle;

    class CircleOcct : public Circle, public OcctObject
    {
        public:
            using Circle::Circle;

            DLL_EXPORT ~CircleOcct() override = default;

            DLL_EXPORT void AssignCanvas(AbstractCanvas *cnv) final;

            DLL_EXPORT void DrawShape() final;

            DLL_EXPORT void RemoveShape() final;

            DLL_EXPORT void ExtractGeomCurves(std::vector<Handle(Geom_Curve)> &container) final;

            DLL_EXPORT void GetAisInteractiveObjects(std::vector<Handle(AIS_InteractiveObject)> &container) final;

        private:
            Handle(AIS_Circle) m_circle = nullptr;
    };
}

#endif // OCCT_CIRCLE_INCLUDED_H
