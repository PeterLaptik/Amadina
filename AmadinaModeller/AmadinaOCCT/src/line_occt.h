#ifndef OCCT_LINE_INCLUDED_H
#define OCCT_LINE_INCLUDED_H

#include "line.h"
#include "occt_object.h"
#include <AIS_Line.hxx>
#include <Geom_CartesianPoint.hxx>

#ifdef _WINDLL
#define DLL_EXPORT __declspec(dllexport)
#else
#define DLL_EXPORT
#endif

namespace cad::model::occt::flat
{
    using cad::model::flat::Line;

    class LineOcct : public Line, public OcctObject
    {
        public:
            using Line::Line;

            DLL_EXPORT ~LineOcct() override = default;

            DLL_EXPORT void AssignCanvas(AbstractCanvas *cnv) final;

            DLL_EXPORT void DrawShape() final;

            DLL_EXPORT void RemoveShape() final;

            DLL_EXPORT void ExtractGeomCurves(std::vector<Handle(Geom_Curve)> &container) final;

            DLL_EXPORT void GetAisInteractiveObjects(std::vector<Handle(AIS_InteractiveObject)> &container) final;

        private:
            Handle(Geom_CartesianPoint) c_point_1 = new Geom_CartesianPoint(0, 0, 0);
            Handle(Geom_CartesianPoint) c_point_2 = new Geom_CartesianPoint(0, 0, 0);
            Handle(AIS_Line) m_line = nullptr;
    };
}

#endif // OCCT_LINE_INCLUDED_H