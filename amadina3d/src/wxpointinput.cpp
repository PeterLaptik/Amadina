#include "wxpointinput.h"
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/sizer.h>

wxPointInput::wxPointInput(wxWindow *parent)
        : FloatingInputBox(parent, wxID_ANY, wxDefaultPosition, wxSize(179,45), wxTAB_TRAVERSAL, wxEmptyString)
{
    wxBoxSizer* v_sizer;
	v_sizer = new wxBoxSizer(wxVERTICAL);

	wxBoxSizer* h_sizer;
	h_sizer = new wxBoxSizer(wxHORIZONTAL);

	m_label = new wxStaticText(this, wxID_ANY, wxT("Point"), wxDefaultPosition, wxDefaultSize, 0);
	m_label->Wrap(-1);
	h_sizer->Add(m_label, 0, wxALL, 5);

	m_input_box = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0);
	h_sizer->Add(m_input_box, 0, wxALL, 5);


	v_sizer->Add(h_sizer, 1, wxEXPAND, 5);

	this->SetSizer(v_sizer);
	this->Layout();
}

wxPointInput::~wxPointInput()
{ }

void wxPointInput::MoveTo(int x, int y)
{

}
