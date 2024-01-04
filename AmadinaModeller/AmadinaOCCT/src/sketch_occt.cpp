#include "sketch_occt.h"
#include "abstract_shape.h"
#include "occt_object_container.h"
#include "occt_canvas.h"
#include <algorithm>

using cad::modeller::occt::shapes2D::OcctObjectContainer;
using cad::modeller::geometry::Direction;
using cad::modeller::geometry::DirectionVector;


cad::modeller::occt::SketchOcct::SketchOcct(const std::string &name)
    : m_name(name)
{ }


void cad::modeller::occt::SketchOcct::Draw(AbstractCanvas &cnv)
{
	auto executor = [&cnv](auto &object)
	{
		object->Draw(cnv);
	};

	std::vector<AbstractShape*> shapes;
	GetShapes(shapes);
	std::for_each(shapes.begin(), shapes.end(), executor);
}

void cad::modeller::occt::SketchOcct::SetDirectionVector(DirectionVector vector)
{
	m_vector = vector;
}

DirectionVector cad::modeller::occt::SketchOcct::GetDirectionVector() const
{
	return m_vector;
}

// TODO Remove
/*
#include <BRepBuilderAPI_MakeEdge.hxx>
#include <BRepBuilderAPI_MakeWire.hxx>
#include <TopoDS_Edge.hxx>
#include <BRepBuilderAPI_MakeFace.hxx>
#include <BRepPrimAPI_MakePrism.hxx>
#include <AIS_Shape.hxx>
void cad::modeller::occt::SketchOcct::ExtractEdges(AbstractCanvas &cnv)
{
	std::vector<Handle(Geom_TrimmedCurve)> curves_container;
	for(const auto &i: m_shapes)
	{
		SketchObject* obj = dynamic_cast<SketchObject*>(i.get());
		obj->GetAisInteractiveObjects(curves_container);
	}

	std::vector<TopoDS_Edge> edges_container;
	for(const auto &i: curves_container)
	{
		edges_container.push_back(BRepBuilderAPI_MakeEdge(i));
	}

	BRepBuilderAPI_MakeWire mk_wire;
	for (const auto &i: edges_container)
	{
		mk_wire.Add(i);
	}

	const TopoDS_Wire &profile = mk_wire.Wire();

	const TopoDS_Face &face = BRepBuilderAPI_MakeFace(profile);

	Direction dir = m_vector.GetDirection();
	gp_Vec prism_vec(dir.GetX(), dir.GetY(), dir.GetZ());
	TopoDS_Shape myBody = BRepPrimAPI_MakePrism(face, prism_vec);

	Handle(AIS_Shape) shape = new AIS_Shape(myBody);
	OcctCanvas &c = static_cast<OcctCanvas &>(cnv);
	c.AddShape(shape);
}
*/