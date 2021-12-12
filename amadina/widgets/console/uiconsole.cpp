#include "uiconsole.h"
#include "../../events/events.h"
#include <wx/textctrl.h>
#include <wx/sizer.h>

// Main console ID assigning for events binding
const long UiConsole::INPUT_TEXT_ID = wxNewId();

wxDEFINE_EVENT(wxCONSOLE_INPUT, wxEventConsoleInput);

BEGIN_EVENT_TABLE(UiConsole, wxPanel)
    EVT_TEXT(UiConsole::INPUT_TEXT_ID, UiConsole::OnInput)
    EVT_TEXT_ENTER(UiConsole::INPUT_TEXT_ID, UiConsole::OnEnter)
END_EVENT_TABLE()


UiConsole::UiConsole(wxWindow *parent,
                    wxWindowID winid,
                    const wxPoint& pos,
                    const wxSize& size,
                    long style,
                    const wxString& name)
    : wxPanel(parent, winid, pos, size, style, name)
{
    wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);
    m_upper_lines = new wxTextCtrl(this, wxNewId(), wxT(""),
                                   wxPoint(-1,-1), wxSize(-1,-1),
                                   wxTE_MULTILINE|wxTE_READONLY);
    sizer->Add(m_upper_lines, 1, wxALL|wxEXPAND, 0);

    m_input_line = new wxTextCtrl(this, INPUT_TEXT_ID, wxT(""),
                                  wxPoint(-1,-1), wxSize(-1,-1),
                                  wxTE_PROCESS_ENTER);

    sizer->Add(m_input_line, 0, wxALL|wxEXPAND, 0);
    SetSizer(sizer);
}

UiConsole::~UiConsole()
{

}

#include <wx/msgdlg.h>
void UiConsole::OnInput(wxCommandEvent &event)
{

}

void UiConsole::OnEnter(wxCommandEvent &event)
{
    wxString line = m_input_line->GetValue();

    if(line=="")
        return;

    // Shift history lines if overflowed
    if(m_history_log.size()==COMMAND_LINE_HISTORY)
    {
        for(int i=0; i<COMMAND_LINE_HISTORY-1; i++)
        {
            m_history_log[i] = std::move(m_history_log[i+1]);
            if(m_command_prompt=="")
                m_history_commands[i] = std::move(m_history_log[i+1]);
        }
        m_history_log[COMMAND_LINE_HISTORY-1] = line;
        if(m_command_prompt=="")
            m_history_commands[COMMAND_LINE_HISTORY-1] = line;
    }
    else
    {
        *m_history_log.end() = line;
    }

    RefreshHistory();
    m_input_line->Clear();
    // Transfer line input to upper listener
    wxEventConsoleInput input_event(line);
    wxPostEvent(this, input_event);
}

void UiConsole::RefreshHistory()
{
    m_upper_lines->Clear();
    for(int i=0; i<m_history_log.size(); i++)
    {
        if(m_history_log[i]=="")
            continue;

        m_upper_lines->AppendText(m_history_log[i]);
        if(i<m_history_log.size()-1)
            m_upper_lines->AppendText('\n');
    }
}

void UiConsole::SetPrompt(const wxString &prompt)
{
    m_command_prompt = prompt;
    m_upper_lines->AppendText('\n');
    m_upper_lines->AppendText(m_command_prompt);
}

void UiConsole::ClearPrompt(void)
{
    m_command_prompt = "";
    m_input_line->Clear();
    RefreshHistory();
}

wxString UiConsole::GetPrompt(void) const
{
    return m_command_prompt;
}

