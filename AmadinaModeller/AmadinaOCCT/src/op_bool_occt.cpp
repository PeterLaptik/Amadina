#include "op_bool_occt.h"
#include "occt_canvas.h"


void cad::model::occt::solid::OpBoolOcct::AssignCanvas(AbstractCanvas *cnv)
{
    AssignOcctCanvas(cnv);
}

bool cad::model::occt::solid::OpBoolOcct::IsValid()
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

void cad::model::occt::solid::OpBoolOcct::GetAisInteractiveObjects(std::vector<Handle(AIS_InteractiveObject)> &container)
{
    if (m_body)
        container.push_back(m_body);
}

void cad::model::occt::solid::OpBoolOcct::ExtractGeomCurves(std::vector<Handle(Geom_Curve)> &container)
{
    //
}