#include "line_occt.h"
#include "occt_canvas.h"

#include <GC_MakeSegment.hxx>
#include <BRepBuilderAPI_MakeEdge.hxx>
#include <BRepBuilderAPI_MakeWire.hxx>


using cad::model::flat::Point;


void cad::model::occt::flat::LineOcct::AssignCanvas(AbstractCanvas *cnv)
{
    AssignOcctCanvas(cnv);
}

void cad::model::occt::flat::LineOcct::DrawShape()
{
    Point pt1 = GetFirstPoint();
    c_point_1->SetX(pt1.GetX());
    c_point_1->SetY(pt1.GetY());
    c_point_1->SetZ(pt1.GetZ());

    Point pt2 = GetSecondPoint();
    c_point_2->SetX(pt2.GetX());
    c_point_2->SetY(pt2.GetY());
    c_point_2->SetZ(pt2.GetZ());
    m_line.reset(new AIS_Line(c_point_1, c_point_2));

    // Output
    ShowOcctObject(m_line);
}

void cad::model::occt::flat::LineOcct::RemoveShape()
{
    HideOcctObject(m_line);
}

void cad::model::occt::flat::LineOcct::ExtractGeomCurves(std::vector<Handle(Geom_Curve)> &container)
{
    const Point &point_1 = GetFirstPoint();
    const Point &point_2 = GetSecondPoint();

    gp_Pnt pt_1(point_1.GetX(), point_1.GetY(), point_1.GetZ());
    gp_Pnt pt_2(point_2.GetX(), point_2.GetY(), point_2.GetZ());

    Handle(Geom_TrimmedCurve) segment = GC_MakeSegment(pt_1, pt_2);
    container.push_back(segment);
}

void cad::model::occt::flat::LineOcct::GetAisInteractiveObjects(std::vector<Handle(AIS_InteractiveObject)> &container)
{
    if (!m_line.IsNull())
        container.push_back(m_line);
}
