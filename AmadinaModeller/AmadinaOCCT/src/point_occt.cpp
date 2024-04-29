#include "point_occt.h"
#include "occt_canvas.h"
#include <Geom_CartesianPoint.hxx>
#include <TopoDS_Vertex.hxx>
#include <BRepBuilderAPI_MakeVertex.hxx>
#include <Prs3d_PointAspect.hxx>


using cad::modeller::AbstractCanvas;


void cad::modeller::occt::shapes2D::PointOcct::AssignCanvas(AbstractCanvas *cnv)
{
	AssignOcctCanvas(cnv);
}

void cad::modeller::occt::shapes2D::PointOcct::Draw()
{
	gp_Pnt pnt(GetX(), GetY(), GetZ());
	TopoDS_Vertex v = BRepBuilderAPI_MakeVertex(pnt);
	m_point.reset(new AIS_Shape(v));

	// Output
	if (GetIsVisible())
		Show();
}

void cad::modeller::occt::shapes2D::PointOcct::Hide()
{
	
	HideOcctObject(m_point);
	SetVisible(false);
}

void cad::modeller::occt::shapes2D::PointOcct::Show()
{
	ShowOcctObject(m_point);
	SetVisible(false);
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
