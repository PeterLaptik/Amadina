#include "op_bool_occt.h"
#include "occt_canvas.h"


void cad::modeller::occt::operations::OpBoolOcct::Show()
{
	auto cnv = GetOcctCanvas();
	if (!cnv)
		return;

	cnv->AddShape(m_body);
}

void cad::modeller::occt::operations::OpBoolOcct::Hide()
{
	auto cnv = GetOcctCanvas();
	if (!cnv)
		return;

	cnv->RemoveShape(m_body);
}

void cad::modeller::occt::operations::OpBoolOcct::AssignCanvas(AbstractCanvas *cnv)
{
	AssignOcctCanvas(cnv);
}

bool cad::modeller::occt::operations::OpBoolOcct::IsValid()
{
	std::vector<AbstractShape *> shapes;
	GetShapes(shapes);

	for (auto shape : shapes)
	{
		auto op = dynamic_cast<AbstractOperation *>(shape);
		if (op && !op->IsValid())
			return false;
	}

	return GetShapesNumber() > 1;
}

void cad::modeller::occt::operations::OpBoolOcct::Refresh()
{
	Hide();
	Draw();
}

void cad::modeller::occt::operations::OpBoolOcct::GetAisInteractiveObjects(std::vector<Handle(AIS_InteractiveObject)> &container)
{
	if (m_body)
		container.push_back(m_body);
}

void cad::modeller::occt::operations::OpBoolOcct::ExtractGeomCurves(std::vector<Handle(Geom_Curve)> &container)
{
}