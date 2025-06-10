#include "sketch_occt.h"
#include "occt_object.h"
#include "occt_canvas.h"
#include <algorithm>

using cad::model::occt::OcctObject;
using cad::model::occt::OcctObject;
using cad::model::geom::Direction;
using cad::model::geom::DirectionVector;

void cad::model::occt::SketchOcct::AssignCanvas(AbstractCanvas *cnv)
{
    AssignOcctCanvas(cnv);
    for (auto shape : m_shapes)
        shape->AssignCanvas(cnv);
}

void cad::model::occt::SketchOcct::AppendObject(AbstractShape *shape)
{
    Sketch::AppendObject(shape);
    shape->AssignCanvas(GetOcctCanvas());
}


void cad::model::occt::SketchOcct::DrawShape()
{
    for (auto shape : m_shapes)
        shape->Draw();
}

void cad::model::occt::SketchOcct::RemoveShape()
{
    for (auto shape : m_shapes)
        shape->Remove();
}

void cad::model::occt::SketchOcct::GetAisInteractiveObjects(std::vector<Handle(AIS_InteractiveObject)> &container)
{
    std::vector<AbstractShape *> shapes;
    GetSubObjects(shapes);

    for (auto shape : shapes)
    {
        auto occt_object = dynamic_cast<OcctObject *>(shape);
        if (occt_object)
            occt_object->GetAisInteractiveObjects(container);
    }
}

void cad::model::occt::SketchOcct::ExtractGeomCurves(std::vector<Handle(Geom_Curve)> &container)
{
    // no curves?
}