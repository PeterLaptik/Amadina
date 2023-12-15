#include "circle_occt.h"
#include "point.h"
#include "occt_canvas.h"
#include <gp_Pnt.hxx>
#include <gp_Circ.hxx>
#include <Geom_Circle.hxx>
#include <Geom_CartesianPoint.hxx>
#include <GC_MakeCircle.hxx>

using Point = cad::modeller::shapes2D::Point;
using Point = cad::modeller::shapes2D::Point;
using Direction = cad::modeller::shapes2D::Direction;

void cad::modeller::occt::shapes2D::CircleOcct::Draw(AbstractCanvas &cnv)
{
	OcctCanvas &canvas = static_cast<OcctCanvas &>(cnv);
	Point center = GetCenter();
	double radius = GetRadius();
	Direction direction = GetDirection();

	gp_Pnt gp_center(center.GetX(), center.GetY(), center.GetZ());

	gp_Dir gp_dir(direction.GetX(), direction.GetY(), direction.GetZ());
	gp_Ax2 gp_ax(gp_center, gp_dir);

	Handle(Geom_Circle) circle = new Geom_Circle(gp_ax, radius);
	m_circle = new AIS_Circle(circle);
	canvas.AddShape(m_circle);
}

void cad::modeller::occt::shapes2D::CircleOcct::GetAisInteractiveObjects(std::vector<Handle(Geom_Curve)> &container)
{
	double radius = GetRadius();

	const Point &point_1 = GetCenter();
	gp_Pnt gp_point(point_1.GetX(), point_1.GetY(), point_1.GetZ());

	Direction dir = GetDirection();
	gp_Dir gp_dir(dir.GetX(), dir.GetY(), dir.GetZ());
	gp_Ax1 gp_axis(gp_point, gp_dir);

	Handle(Geom_Circle) segment = GC_MakeCircle(gp_axis, radius);
	container.push_back(segment);
}
