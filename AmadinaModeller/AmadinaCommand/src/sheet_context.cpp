#include "sheet_context.h"
#include "model_tree.h"
#include "sketch.h"

using cad::model::AbstractCanvas;
using cad::model::flat::Sketch;


cad::app::SheetContext::SheetContext(cad::app::ApplicationContext *app_ctx)
    : m_app_context(app_ctx)
{ }

void cad::app::SheetContext::SetModelTree(ModelTree *model_tree)
{
    m_model_tree = model_tree;
}

void cad::app::SheetContext::SetActiveSketch(Sketch* sketch)
{
    m_active_sketch = sketch;
}

void cad::app::SheetContext::DeactivateSketch()
{
    m_active_sketch = nullptr;
}

cad::model::flat::Sketch* cad::app::SheetContext::GetActiveSketch()
{
    return m_active_sketch;
}
