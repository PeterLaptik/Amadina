#include "point_occt.h"
#include "occt_canvas.h"
#include <Geom_CartesianPoint.hxx>


using cad::modeller::AbstractCanvas;


void cad::modeller::occt::shapes2D::PointOcct::AssignCanvas(AbstractCanvas *cnv)
{
	AssignOcctCanvas(cnv);
}

void cad::modeller::occt::shapes2D::PointOcct::Draw()
{
	auto cnv = GetOcctCanvas();

	if (!cnv)
		return;

	Handle(Geom_Point) c_point = new Geom_CartesianPoint(GetX(), GetY(), GetZ());
	m_point.reset(new AIS_Point(c_point));

	// Output
	if (GetIsVisible())
		Show();
}

void cad::modeller::occt::shapes2D::PointOcct::Hide()
{
	auto cnv = GetOcctCanvas();

	if (!cnv)
		return;

	cnv->RemoveShape(m_point);
}

void cad::modeller::occt::shapes2D::PointOcct::Refresh()
{
	Hide();
	Draw();
}

void cad::modeller::occt::shapes2D::PointOcct::ExtractGeomCurves(std::vector<Handle(Geom_Curve)> &container)
{
	// no curves for point
}

void cad::modeller::occt::shapes2D::PointOcct::GetAisInteractiveObjects(std::vector<Handle(AIS_InteractiveObject)> &container)
{
	container.push_back(m_point);
}
