#include "occt_object.h"


using cad::model::occt::OcctCanvas;


void cad::model::occt::OcctObject::AssignOcctCanvas(AbstractCanvas *cnv)
{
    m_canvas = static_cast<OcctCanvas *>(cnv);
}

void cad::model::occt::OcctObject::HideOcctObject(Handle(AIS_InteractiveObject) shape)
{
    if (!m_canvas)
        return;

    m_canvas->RemoveShape(shape);
}

void cad::model::occt::OcctObject::ShowOcctObject(Handle(AIS_InteractiveObject) shape)
{
    if (!m_canvas)
        return;

    m_canvas->AddShape(shape);
}

OcctCanvas* cad::model::occt::OcctObject::GetOcctCanvas() const
{
    return m_canvas;
}