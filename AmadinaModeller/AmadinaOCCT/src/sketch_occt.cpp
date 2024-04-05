#include "sketch_occt.h"
#include "occt_object.h"
#include "occt_canvas.h"
#include <algorithm>

using cad::modeller::occt::OcctObject;
using cad::modeller::occt::OcctObject;
using cad::modeller::geometry::Direction;
using cad::modeller::geometry::DirectionVector;


cad::modeller::occt::SketchOcct::SketchOcct(const std::string &name)
    : m_name(name)
{ }


void cad::modeller::occt::SketchOcct::AssignCanvas(AbstractCanvas *cnv)
{
	AssignOcctCanvas(cnv);
	for (auto shape : m_shapes)
		shape->AssignCanvas(cnv);
}


void cad::modeller::occt::SketchOcct::Draw()
{
	for (auto shape : m_shapes)
		shape->Draw();

	if (GetIsVisible())
		Show();

}

void cad::modeller::occt::SketchOcct::Hide()
{
	for (auto shape : m_shapes)
		shape->Hide();
}

void cad::modeller::occt::SketchOcct::Show()
{
	std::for_each(m_shapes.begin(), m_shapes.end(),
		[this](auto object) {
			object->Show();
		});
}

void cad::modeller::occt::SketchOcct::Refresh()
{
	Hide();
	//Draw();
	if (GetIsVisible())
		Show();
}

void cad::modeller::occt::SketchOcct::SetDirectionVector(const DirectionVector &vector)
{
	m_vector = vector;
}

DirectionVector cad::modeller::occt::SketchOcct::GetDirectionVector() const
{
	return m_vector;
}

void cad::modeller::occt::SketchOcct::GetAisInteractiveObjects(std::vector<Handle(AIS_InteractiveObject)> &container)
{
	std::vector<AbstractShape*> shapes;
	GetSubObjects(shapes);

	for (auto shape : shapes)
	{
		auto occt_object = dynamic_cast<OcctObject*>(shape);
		if (occt_object)
			occt_object->GetAisInteractiveObjects(container);
	}
}

void cad::modeller::occt::SketchOcct::ExtractGeomCurves(std::vector<Handle(Geom_Curve)> &container)
{
	// no curves?
}