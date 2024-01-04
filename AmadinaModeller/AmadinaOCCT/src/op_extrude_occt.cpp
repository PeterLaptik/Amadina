#include "abstract_shape.h"
#include "op_extrude_occt.h"
#include "sketch_occt.h"
#include "occt_object_container.h"
#include "direction.h"
#include "occt_canvas.h"
#include <BRepBuilderAPI_MakeEdge.hxx>
#include <BRepBuilderAPI_MakeWire.hxx>
#include <TopoDS_Edge.hxx>
#include <BRepBuilderAPI_MakeFace.hxx>
#include <BRepPrimAPI_MakePrism.hxx>
#include <AIS_Shape.hxx>
#include<Geom_TrimmedCurve.hxx>

using cad::modeller::AbstractShape;
using cad::modeller::geometry::Direction;
using cad::modeller::occt::shapes2D::OcctObjectContainer;

void cad::modeller::occt::operations::OpExtrudeOcct::Draw(AbstractCanvas &cnv)
{
	// Has no sketch
	if (!IsValid())
		return;

	const AbstractShape* shape = GetSketch();
	const SketchOcct *sketch = dynamic_cast<const SketchOcct*>(shape);

	// Object is impossible to draw
	if (sketch == nullptr)
		return;
	
	std::vector<AbstractShape*> shapes_container;
	std::vector<Handle(Geom_Curve)> curves_container;

	// Get objects to extract
	sketch->GetShapes(shapes_container);
	for (const auto &shape : shapes_container)
	{
		auto *obj = dynamic_cast<OcctObjectContainer*>(shape);
		if (obj == nullptr)
			continue;

		obj->ExtractGeomCurves(curves_container);
	}

	if (shapes_container.empty())
		return;

	// Get edges
	std::vector<TopoDS_Edge> edges_container;
	for (Handle(Geom_Curve) geom_obj: curves_container)
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
	TopoDS_Shape myBody = BRepPrimAPI_MakePrism(face, prism_vec);

	
	Handle(AIS_Shape) ais_shape = new AIS_Shape(myBody);
	OcctCanvas &canvas = static_cast<OcctCanvas &>(cnv);
	canvas.AddShape(ais_shape);
}

bool cad::modeller::occt::operations::OpExtrudeOcct::IsValid()
{
	return GetSketch() != nullptr;
}

void cad::modeller::occt::operations::OpExtrudeOcct::Purge(std::vector<AbstractShape*> &container)
{
	const AbstractShape *sketch = GetSketch();
	for (auto obj : container)
	{
		if (obj == sketch)
		{
			SetSketch(nullptr);
			return;
		}
	}
}
