#include "abstract_shape.h"
#include "op_extrude_occt.h"
#include "sketch_occt.h"
#include "occt_object.h"
#include "direction.h"
#include "occt_canvas.h"
#include <algorithm>
#include <BRepBuilderAPI_MakeEdge.hxx>
#include <BRepBuilderAPI_MakeWire.hxx>
#include <TopoDS_Edge.hxx>
#include <BRepBuilderAPI_MakeFace.hxx>
#include <BRepPrimAPI_MakePrism.hxx>
#include <AIS_Shape.hxx>
#include <Geom_Curve.hxx>
#include <Geom_TrimmedCurve.hxx>


using cad::model::AbstractShape;
using cad::model::geom::Direction;
using cad::model::geom::DirectionVector;
using cad::model::occt::OcctObject;


void cad::model::occt::solid::OpExtrudeOcct::AssignCanvas(AbstractCanvas *cnv)
{
    AssignOcctCanvas(cnv);
}

void cad::model::occt::solid::OpExtrudeOcct::DrawShape()
{
    // Has no sketch
    if (!IsValid())
    {
        m_body.Nullify();
        return;
    }

    // TODO remove dynamic cast?
    AbstractShape *shape_sketch = GetSketch();
    auto *sketch = dynamic_cast<SketchOcct *>(shape_sketch);

    // Object is impossible to extrude. Only sketch is allowed
    if (sketch == nullptr)
        return;

    std::vector<AbstractShape *> shapes_container;
    std::vector<Handle(Geom_Curve)> curves_container;

    // Get objects to extract
    sketch->GetSubObjects(shapes_container);
    for (const auto &element : shapes_container)
    {
        auto *obj = dynamic_cast<OcctObject *>(element);
        if (obj == nullptr)
            continue;

        obj->ExtractGeomCurves(curves_container);
    }

    if (shapes_container.empty())
        return;

    // Get edges
    std::vector<TopoDS_Edge> edges_container;
    for (Handle(Geom_Curve) geom_obj : curves_container)
    {
        edges_container.push_back(BRepBuilderAPI_MakeEdge(geom_obj));
    }

    // Create wire from edges
    BRepBuilderAPI_MakeWire mk_wire;
    for (const auto &i : edges_container)
    {
        mk_wire.Add(i);
    }

    // Create face
    const TopoDS_Wire &profile = mk_wire.Wire();
    const TopoDS_Face &face = BRepBuilderAPI_MakeFace(profile);

    // Extrude
    double extrude_length = GetLength();
    const DirectionVector dir_vector = sketch->GetDirectionVector();
    Direction dir = dir_vector.GetDirection();
    gp_Vec prism_vec(dir.GetX() * extrude_length, dir.GetY() * extrude_length, dir.GetZ() * extrude_length);
    TopoDS_Shape body_new = BRepPrimAPI_MakePrism(face, prism_vec);

    // Result
    m_body.reset(new AIS_Shape(body_new));

    // Output
    ShowOcctObject(m_body);
}

void cad::model::occt::solid::OpExtrudeOcct::RemoveShape()
{
    HideOcctObject(m_body);
}


bool cad::model::occt::solid::OpExtrudeOcct::IsValid()
{
    return GetSketch() != nullptr;
}

void cad::model::occt::solid::OpExtrudeOcct::GetAisInteractiveObjects(std::vector<Handle(AIS_InteractiveObject)> &container)
{
    if (m_body)
        container.push_back(m_body);
}

void cad::model::occt::solid::OpExtrudeOcct::ExtractGeomCurves(std::vector<Handle(Geom_Curve)> &container)
{
    // not used
}


