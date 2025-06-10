#ifndef OCCT_SKETCH_INCLUDED_H
#define OCCT_SKETCH_INCLUDED_H

#include "sketch.h"
#include "occt_object.h"

#ifdef _WINDLL
#define DLL_EXPORT __declspec(dllexport)
#else
#define DLL_EXPORT
#endif

namespace cad::model::occt
{
    using cad::model::flat::Sketch;

    ///\brief Sketch draft is assembled from 2D elements (e.g. points, lines, circles etc.)
    class SketchOcct : public Sketch, public OcctObject
    {
        public:
            using Sketch::Sketch;

            DLL_EXPORT ~SketchOcct() override = default;

            DLL_EXPORT void AssignCanvas(AbstractCanvas *cnv) final;

            DLL_EXPORT void AppendObject(AbstractShape *shape) override;

            DLL_EXPORT void DrawShape() final;

            DLL_EXPORT void RemoveShape() final;

            DLL_EXPORT void GetAisInteractiveObjects(std::vector<Handle(AIS_InteractiveObject)> &container) final;

            DLL_EXPORT void ExtractGeomCurves(std::vector<Handle(Geom_Curve)> &container) final;
    };
}

#endif // OCCT_SKETCH_INCLUDED_H

