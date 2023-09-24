#include "point.h"
#include "line_occt.h"
#include "occt_canvas.h"
#include <Geom_CartesianPoint.hxx>
#include <GC_MakeSegment.hxx>
#include <BRepBuilderAPI_MakeEdge.hxx>
#include <BRepBuilderAPI_MakeWire.hxx>

using cad::modeller::shapes2D::Point;

void cad::modeller::occt::shapes2D::LineOcct::Draw(AbstractCanvas &cnv)
{
	using cad::modeller::shapes2D::Point;
	Point pt1 = GetFirstPoint();
	Handle(Geom_Point) c_point_1 = new Geom_CartesianPoint(pt1.GetX(), pt1.GetY(), pt1.GetZ());
	Point pt2 = GetSecondPoint();
	Handle(Geom_Point) c_point_2 = new Geom_CartesianPoint(pt2.GetX(), pt2.GetY(), pt2.GetZ());
	Handle(AIS_Line) line = new AIS_Line(c_point_1, c_point_2);
	OcctCanvas &c = static_cast<OcctCanvas &>(cnv);
	c.AddShape(line);
}

void cad::modeller::occt::shapes2D::LineOcct::GetAisInteractiveObjects(std::vector<Handle(Geom_TrimmedCurve)> &container)
{
	const Point &point_1 = GetFirstPoint();
	const Point &point_2 = GetSecondPoint();

	gp_Pnt pt_1(point_1.GetX(), point_1.GetY(), point_1.GetZ());
	gp_Pnt pt_2(point_2.GetX(), point_2.GetY(), point_2.GetZ());

	Handle(Geom_TrimmedCurve) segment = GC_MakeSegment(pt_1, pt_2);
	container.push_back(segment);
}

