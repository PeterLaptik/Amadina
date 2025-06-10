#include "wxmodeller3d.h"
#include "sheet_context.h"
#include "wxoccpanel.h"
#include "wxmodeltree.h"
#include <wx/sizer.h>
#include <wx/treectrl.h>
#include <wx/splitter.h>

const char *ROOT_NODE_NAME = "Model";

wxModeller3D::wxModeller3D(wxWindow *parent, ApplicationContext *app_ctx)
    : wxAbstractModeller(parent, wxID_ANY, wxDefaultPosition, 
        wxDefaultSize, wxTAB_TRAVERSAL | wxNO_BORDER, wxPanelNameStr),
    m_app_context(app_ctx)
{
    m_sheet_context = new SheetContext(app_ctx);

    m_sizer = new wxBoxSizer(wxHORIZONTAL);
    m_splitter = new wxSplitterWindow(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSP_3D);
    m_sizer->Add(m_splitter, 5, wxEXPAND | wxALL, 5);

    m_occpanel = new wxOccPanel(m_splitter);
    //m_occpanel->SetStyle(m_styles_container.GetStyle("default"));

    m_model_tree = new wxModelTree(m_splitter, m_occpanel);
    m_model_tree->SetBackgroundColour(wxColor(204, 204, 204));
    m_model_tree->AddRoot(ROOT_NODE_NAME);

    m_splitter->SplitVertically(m_model_tree, m_occpanel, 342);

    m_sheet_context->SetModelTree(m_model_tree);

	this->SetSizer(m_sizer);
}

wxModeller3D::~wxModeller3D()
{
    delete m_sheet_context;
}

void wxModeller3D::RefreshView(void)
{

}

SheetContext* wxModeller3D::GetContext()
{
    return m_sheet_context;
}


#include "point_occt.h"
#include "line_occt.h"
#include "circle_occt.h"
#include "direction_vector.h"
#include "sketch_occt.h"
#include "op_extrude_occt.h"
#include "op_bool_fuse_occt.h"
#include "op_bool_common_occt.h"
void wxModeller3D::Test()
{
    using cad::model::flat::Point;
    using cad::model::flat::Line;
    using cad::model::flat::Direction;
    using cad::model::geom::DirectionVector;
    using cad::model::occt::flat::PointOcct;
    using cad::model::occt::flat::LineOcct;
    using cad::model::occt::flat::CircleOcct;
    using cad::model::occt::solid::OpBoolOcct;
    using cad::model::occt::solid::OpBoolCommonOcct;
    using cad::model::occt::solid::OpBoolFuseOcct;
    using cad::model::occt::SketchOcct;
    using cad::model::occt::solid::OpExtrudeOcct;

    // Sketch square
    SketchOcct *sketch = new SketchOcct("Test");

    sketch->AppendObject(new LineOcct(PointOcct(0, 0), PointOcct(0, 200)));
    sketch->AppendObject(new LineOcct(PointOcct(0, 200), PointOcct(200, 200)));
    sketch->AppendObject(new LineOcct(PointOcct(200, 200), PointOcct(200, 0)));
    sketch->AppendObject(new LineOcct(PointOcct(200, 0), PointOcct(0, 0)));

    // Points
    sketch->AppendObject(new PointOcct(8, 8));
    sketch->AppendObject(new PointOcct(4, 4));
    sketch->AppendObject(new PointOcct(3, 3));

    SketchOcct *sketch_2 = new SketchOcct("Test_2");

    Point c_c(0, 0, 50);
    CircleOcct *circle_obj = new CircleOcct(c_c, 150.0);
    Direction angles(1, 0, 0);
    circle_obj->SetDirection(angles);
    sketch_2->SetDirectionVector(DirectionVector(c_c, angles));
    sketch_2->AppendObject(circle_obj);

    OpExtrudeOcct *op_extrude = new OpExtrudeOcct(sketch, 50);
    OpExtrudeOcct *op_extrude2 = new OpExtrudeOcct(sketch_2, 50);

    m_model_tree->AddItem(sketch);
    m_model_tree->AddItem(sketch_2);

    m_model_tree->AddItem(op_extrude);
    m_model_tree->AddItem(op_extrude2);

    OpBoolOcct *fuse = new OpBoolFuseOcct();
    fuse->AddShape(op_extrude);
    fuse->AddShape(op_extrude2);
    m_model_tree->AddItem(fuse);
}
