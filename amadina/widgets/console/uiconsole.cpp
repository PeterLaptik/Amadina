#include "uiconsole.h"
#include "../../events/events.h"
#include <wx/textctrl.h>
#include <wx/sizer.h>

// Main console ID assigning for events binding
const long UiConsole::INPUT_TEXT_ID = wxNewId();

wxDEFINE_EVENT(wxCONSOLE_INPUT, wxEventConsoleInput);

BEGIN_EVENT_TABLE(UiConsole, wxPanel)
    //EVT_TEXT(UiConsole::INPUT_TEXT_ID, UiConsole::OnInput)
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

//void UiConsole::OnInput(wxCommandEvent &event)
//{
//
//}

void UiConsole::OnEnter(wxCommandEvent &event)
{
    wxString line = m_input_line->GetValue();

    if(line=="")
        return;

    AppendCommand(line);
    RefreshHistory();
    m_input_line->Clear();
    // Transfer line input to upper listener
    wxEventConsoleInput input_event(line);
    wxPostEvent(this, input_event);
}

#include <wx/msgdlg.h>
void UiConsole::ShowPrevious()
{
    int cursor = GetCurrentInputLogPosition();
    --cursor;
    if(cursor>=0 && cursor<COMMAND_LINE_HISTORY)
        if(!m_command_log[cursor].IsEmpty()) // may be empty cell
            m_input_line->SetValue(m_command_log[cursor]);
}

void UiConsole::ShowNext()
{
    int cursor = GetCurrentInputLogPosition();
    ++cursor;
    if(cursor>=0 && cursor<COMMAND_LINE_HISTORY)
        if(!m_command_log[cursor].IsEmpty()) // may be empty cell
            m_input_line->SetValue(m_command_log[cursor]);
}

int UiConsole::GetCurrentInputLogPosition()
{
    wxString entered = m_input_line->GetValue();
    int cursor = 0;
    for(; cursor<COMMAND_LINE_HISTORY; cursor++)
    {
        if(m_command_log[cursor].IsEmpty())
            continue;

        if(m_command_log[cursor]==entered)
            break;
    }
    return cursor;
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
void UiConsole::AppendCommand(const wxString &cmd)
{
    for(int i=0; i<m_command_log.size(); i++)
    {
        if(m_command_log[i]==cmd)
            goto exit_logging;
    }
    // Add to command log
    if(m_command_log.size()>=COMMAND_LINE_HISTORY)
    {
        for(int i=0; i<COMMAND_LINE_HISTORY-1; i++)
            m_command_log[i] = m_command_log[i+1];
        m_command_log[COMMAND_LINE_HISTORY-1] = cmd;
    }
    else
    {
        m_command_log[m_command_log.size()-1] = cmd;
    }

    exit_logging:
    AppendMessage(cmd);
}

void UiConsole::AppendMessage(const wxString &msg)
{
    if(m_history_log.size()>=COMMAND_LINE_HISTORY)
    {
        for(int i=0; i<COMMAND_LINE_HISTORY-1; i++)
            m_history_log[i] = m_history_log[i+1];
        m_history_log[COMMAND_LINE_HISTORY-1] = msg;
    }
    else
    {
        m_history_log[m_history_log.size()-1] = msg;
    }
}

void UiConsole::SendText(const wxString &txt, bool is_command)
{
    if(is_command)
        AppendCommand(txt);
    else
        AppendMessage(txt);
    RefreshHistory();
}

