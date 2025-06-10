#include "point_occt.h"
#include "occt_canvas.h"
#include <Geom_CartesianPoint.hxx>
#include <TopoDS_Vertex.hxx>
#include <BRepBuilderAPI_MakeVertex.hxx>
#include <Prs3d_PointAspect.hxx>


using cad::model::AbstractCanvas;


void cad::model::occt::flat::PointOcct::AssignCanvas(AbstractCanvas *cnv)
{
    AssignOcctCanvas(cnv);
}

void cad::model::occt::flat::PointOcct::DrawShape()
{
    gp_Pnt pnt(GetX(), GetY(), GetZ());
    TopoDS_Vertex v = BRepBuilderAPI_MakeVertex(pnt);
    m_point.reset(new AIS_Shape(v));

    // Output
    ShowOcctObject(m_point);
}

void cad::model::occt::flat::PointOcct::RemoveShape()
{

    HideOcctObject(m_point);
}

void cad::model::occt::flat::PointOcct::ExtractGeomCurves(std::vector<Handle(Geom_Curve)> &container)
{
    // no curves for point
}

void cad::model::occt::flat::PointOcct::GetAisInteractiveObjects(std::vector<Handle(AIS_InteractiveObject)> &container)
{
    container.push_back(m_point);
}
