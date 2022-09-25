#include "wxmodeller3d.h"
#include "wxoccpanel.h"
#include <wx/sizer.h>
#include <wx/treectrl.h>
#include <wx/splitter.h>

wxModeller3D::wxModeller3D(wxWindow *parent,
                       wxWindowID winid,
                       const wxPoint &pos,
                       const wxSize &size,
                       long style,
                       const wxString &name)
    : wxPanel(parent, winid, pos, size, style, name)
{
    m_sizer = new wxBoxSizer(wxHORIZONTAL);
    m_splitter = new wxSplitterWindow(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSP_3D);
    m_sizer->Add(m_splitter, 5, wxEXPAND | wxALL, 5);

    m_model_tree = new wxTreeCtrl(m_splitter);
    m_model_tree->SetBackgroundColour(wxColor(204,204,204));
    m_model_tree->AddRoot("History");
    m_occpanel = new wxOccPanel(m_splitter);
    m_splitter->SplitVertically(m_model_tree, m_occpanel, 342);

	this->SetSizer(m_sizer);
}

wxModeller3D::~wxModeller3D()
{ }

void wxModeller3D::Test()
{
    m_occpanel->Test();
}
