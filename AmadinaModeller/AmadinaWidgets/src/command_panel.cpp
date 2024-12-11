#include "command_panel.h"

const int MAX_COMMAND_LINE_LENGTH = 255;
const int MAX_COMMAND_LINE_HISTORY = 15;

///\ TODO Desctiption
// --------------------------------------
// |                                    |
// |     History text box               |
// |                                    |
// --------------------------------------
// |      Input text box                |
// --------------------------------------

CommandPanel::CommandPanel(wxWindow *parent, wxWindowID id)
    : wxPanel(parent, id)
{
    wxBoxSizer *m_main_sizer = new wxBoxSizer(wxVERTICAL);
    // Upper history text box: multiline list of previous commands
    m_txt_history = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize,
                                    wxTE_MULTILINE | wxTE_READONLY | wxTE_RICH2);
    m_main_sizer->Add(m_txt_history, 1, wxEXPAND | wxALL);
    // Bottom input text box
    m_txt_input = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize,
                                 wxTE_PROCESS_TAB | wxTE_PROCESS_ENTER);
    m_txt_input->SetMaxLength(MAX_COMMAND_LINE_LENGTH);
    m_main_sizer->Add(m_txt_input, 0, wxEXPAND | wxALL);
    SetSizer(m_main_sizer);

    m_txt_input->Bind(wxEVT_CHAR, &CommandPanel::OnChar, this);
}

void CommandPanel::InputText(const wxString &txt)
{
    if (txt.length() < 1)
        return;

    m_cmd_history.push_back(txt.ToStdString());
    m_txt_history->AppendText(txt);
    m_txt_history->AppendText('\n');

    if (m_txt_history->GetNumberOfLines() >= MAX_COMMAND_LINE_HISTORY)
    {
        DeleteHistoryTopLine();
    }
}

void CommandPanel::SendMessage(const wxString &txt)
{
    InputText(txt);
}

void CommandPanel::SetAutocompleteList(const std::vector<std::string> *list)
{
    m_autocompleter.SetCommandList(list);
}

void CommandPanel::OnChar(wxKeyEvent &event)
{
    int code = event.GetKeyCode();
    // Input text
    if(code == WXK_RETURN)
    {
        m_txt_input->GetLineText(0);
        InputText(m_txt_input->GetValue());
        m_txt_input->Clear();
        return;
    }
    // Show autocomplete proposal
    if(code == WXK_TAB)
    {
        ProposeCommandByFirstChars();
        return;
    }
    // Show previous commands (keys up / down)
    if (code == WXK_UP || code == WXK_DOWN)
    {
        ExtractHistoryLine(code);
        return;
    }
    m_cmd_history_cursor = -1;
    event.Skip();
}

void CommandPanel::DeleteHistoryTopLine()
{
    int remove_pos = m_txt_history->GetLineLength(0) + 1;
    assert(remove_pos > -1);
    m_txt_history->Remove(0, remove_pos);
    m_cmd_history.pop_front();
}

void CommandPanel::ProposeCommandByFirstChars()
{
    const wxString &txt = m_txt_input->GetValue();
    if (txt.Find(' ') != -1) // Only first word autocomplete is allowed
        return;

    bool has_choise = m_autocompleter.SetNextChoiceFor(txt.ToStdString());
    if (has_choise)
    {
        m_txt_input->SetValue(m_autocompleter.GetNextChoice());
        m_txt_input->SetInsertionPoint(m_txt_input->GetLastPosition());
    }
}

void CommandPanel::ExtractHistoryLine(int key_code)
{
    int d_size = static_cast<int>(m_cmd_history.size());
    int incrementor = key_code == WXK_UP ? -1 : +1;

    if (m_cmd_history_cursor == -1)
        m_cmd_history_cursor = d_size;

    m_cmd_history_cursor += incrementor;

    if (m_cmd_history_cursor >= 0 && m_cmd_history_cursor < d_size)
    {
        m_txt_input->SetValue(m_cmd_history[m_cmd_history_cursor]);
        m_txt_input->SetInsertionPoint(m_txt_input->GetLastPosition());
    }
    else
    {
        m_cmd_history_cursor -= incrementor;
    }
}
