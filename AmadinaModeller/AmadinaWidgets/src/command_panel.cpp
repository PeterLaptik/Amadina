#include "command_panel.h"
#include "command_autocompleter_vec.h"

const int MAX_COMMAND_LINE_LENGTH = 255;
const int MAX_COMMAND_LINE_VISIBLE_HISTORY = 15;

CommandPanel::CommandPanel(wxWindow *parent, wxWindowID id)
    : wxPanel(parent, id)
{
    wxBoxSizer *m_main_sizer = new wxBoxSizer(wxVERTICAL);

    m_txt_history = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize,
                                    wxTE_MULTILINE | wxTE_READONLY | wxTE_RICH2);
    m_main_sizer->Add(m_txt_history, 1, wxEXPAND | wxALL);

    m_txt_input = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize,
                                 wxTE_PROCESS_TAB | wxTE_PROCESS_ENTER);
    m_txt_input->SetMaxLength(MAX_COMMAND_LINE_LENGTH);
    m_main_sizer->Add(m_txt_input, 0, wxEXPAND | wxALL);

    SetSizer(m_main_sizer);

    m_txt_input->Bind(wxEVT_CHAR, &CommandPanel::OnChar, this);
    m_autocompleter = std::make_unique<CommandAutocompliterVec>();
}

void CommandPanel::InputText(const wxString &txt)
{
    if (txt.length() < 1)
        return;

    if (m_txt_history->GetNumberOfLines() >= MAX_COMMAND_LINE_VISIBLE_HISTORY)
    {
        DeleteHistoryTopLine();
    }

    m_txt_history->AppendText(txt);
    m_txt_history->AppendText('\n');
}

void CommandPanel::SetAutocompleteList(const std::vector<std::string> *list)
{
    m_autocompleter->SetCommandList(list);
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
        ProposeCommandByFirstChars();
        return;
    }

    event.Skip();
}

void CommandPanel::DeleteHistoryTopLine()
{
    int remove_pos = m_txt_history->GetLineLength(0) + 1;
    assert(remove_pos > -1);
    m_txt_history->Remove(0, remove_pos);
}

void CommandPanel::ProposeCommandByFirstChars()
{
    wxString &txt = m_txt_input->GetValue();
    if (txt.Find(' ') != -1)
        return;

    bool has_choise = m_autocompleter->SetNextChoiceFor(txt.ToStdString());
    if (has_choise)
    {
        m_txt_input->SetValue(m_autocompleter->GetNextChoice());
        m_txt_input->SetInsertionPoint(m_txt_input->GetLastPosition());
    }
}
