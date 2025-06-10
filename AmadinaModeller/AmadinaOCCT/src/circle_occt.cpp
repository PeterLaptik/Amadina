#include "circle_occt.h"
#include <gp_Pnt.hxx>
#include <gp_Circ.hxx>
#include <Geom_Circle.hxx>
#include <Geom_CartesianPoint.hxx>
#include <GC_MakeCircle.hxx>

using cad::model::flat::Point;
using cad::model::flat::Point;
using cad::model::flat::Direction;


void cad::model::occt::flat::CircleOcct::AssignCanvas(AbstractCanvas *cnv)
{
    AssignOcctCanvas(cnv);
}

void cad::model::occt::flat::CircleOcct::DrawShape()
{
    Point center = GetCenter();
    double radius = GetRadius();
    Direction direction = GetDirection();

    gp_Pnt gp_center(center.GetX(), center.GetY(), center.GetZ());

    gp_Dir gp_dir(direction.GetX(), direction.GetY(), direction.GetZ());
    gp_Ax2 gp_ax(gp_center, gp_dir);

    Handle(Geom_Circle) circle = new Geom_Circle(gp_ax, radius);
    m_circle.reset(new AIS_Circle(circle));

    // Output
    ShowOcctObject(m_circle);
}

void cad::model::occt::flat::CircleOcct::RemoveShape()
{
    HideOcctObject(m_circle);
}

void cad::model::occt::flat::CircleOcct::ExtractGeomCurves(std::vector<Handle(Geom_Curve)> &container)
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

void cad::model::occt::flat::CircleOcct::GetAisInteractiveObjects(std::vector<Handle(AIS_InteractiveObject)> &container)
{
    if (!m_circle.IsNull())
        container.push_back(m_circle);
}
