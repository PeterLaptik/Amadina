#include "circle_occt.h"
#include "occt_canvas.h"
#include <gp_Pnt.hxx>
#include <gp_Circ.hxx>
#include <Geom_Circle.hxx>
#include <Geom_CartesianPoint.hxx>

void cad::modeller::occt::shapes2D::CircleOcct::Draw(AbstractCanvas &cnv)
{
	using cad::modeller::shapes2D::Point;
	using cad::modeller::shapes2D::Direction;

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

void cad::modeller::occt::shapes2D::CircleOcct::GetAisInteractiveObjects(std::vector<Handle(Geom_TrimmedCurve)> &container)
{
	// empty implementation
}
