#include "point_occt.h"
#include "occt_canvas.h"
#include <Geom_CartesianPoint.hxx>

using cad::modeller::AbstractCanvas;

void cad::modeller::occt::shapes2D::PointOcct::Draw(AbstractCanvas &cnv)
{
	OcctCanvas &canvas = static_cast<OcctCanvas &>(cnv);
	Handle(Geom_Point) c_point = new Geom_CartesianPoint(GetX(), GetY(), GetZ());
	m_point = new AIS_Point(c_point);
	canvas.AddShape(m_point);
}

void cad::modeller::occt::shapes2D::PointOcct::ExtractGeomCurves(std::vector<Handle(Geom_Curve)> &container)
{
	// empty implementation
}

void cad::modeller::occt::shapes2D::PointOcct::GetAisInteractiveObjects(std::vector<Handle(AIS_InteractiveObject)> &container)
{
	
}
