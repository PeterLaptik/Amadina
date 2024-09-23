#include "command_panel.h"

const int MAX_COMMAND_LINE_LENGTH = 255;
const int MAX_COMMAND_LINE_VISIBLE_HISTORY = 20;

CommandPanel::CommandPanel(wxWindow *parent, wxWindowID id)
    : wxPanel(parent, id)
{
    m_main_sizer = new wxBoxSizer(wxVERTICAL);

    m_txt_history = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize,
                                    wxTE_MULTILINE | wxTE_READONLY);
    m_main_sizer->Add(m_txt_history, 0, wxEXPAND | wxALL, 0, nullptr);

    m_txt_input = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize,
                                 wxTE_PROCESS_TAB | wxTE_PROCESS_ENTER);
    m_txt_input->SetMaxLength(MAX_COMMAND_LINE_LENGTH);
    m_main_sizer->Add(m_txt_input, 0, wxEXPAND | wxALL, 0, nullptr);

    SetSizer(m_main_sizer);

    m_txt_input->Bind(wxEVT_CHAR, &CommandPanel::OnChar, this);
}

void CommandPanel::InputText(const wxString &txt)
{
    m_txt_history->AppendText(txt);
    m_txt_history->AppendText('\n');
}

void CommandPanel::OnChar(wxKeyEvent &event)
{
    int code = event.GetKeyCode();
    if(code == WXK_RETURN)
    {
        InputText(m_txt_input->GetValue());
        m_txt_input->Clear();
        return;
    }

    if(code == WXK_TAB)
    {
        SearchCommandByMask();
        return;
    }

    event.Skip();
}

void CommandPanel::SearchCommandByMask()
{

}
