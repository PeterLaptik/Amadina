#ifndef UICONSOLE_H_INCLUDED
#define UICONSOLE_H_INCLUDED

#include <wx/panel.h>
#include <array>

static const char *CLASS_NAME_UI_CONSOLE = "UI console";

class wxTextCtrl;

class UiConsole: public wxPanel
{
    public:
        UiConsole(wxWindow *parent,
                wxWindowID winid = wxID_ANY,
                const wxPoint& pos = wxDefaultPosition,
                const wxSize& size = wxDefaultSize,
                long style = wxTAB_TRAVERSAL | wxNO_BORDER,
                const wxString& name = CLASS_NAME_UI_CONSOLE);

        virtual ~UiConsole();

        void SetPrompt(const wxString &prompt);
        void ClearPrompt(void);
        wxString GetPrompt(void) const;

    protected:
        void OnInput(wxCommandEvent &event);
        void OnEnter(wxCommandEvent &event);

    private:
        inline void RefreshHistory(void);

        static const size_t COMMAND_LINE_HISTORY = 100;
        static const long INPUT_TEXT_ID;
        wxString m_command_prompt;

        wxTextCtrl *m_input_line;
        wxTextCtrl *m_upper_lines;
        std::array<wxString,COMMAND_LINE_HISTORY> m_history_log;
        std::array<wxString,COMMAND_LINE_HISTORY> m_history_commands;

        DECLARE_EVENT_TABLE()
};

#endif // UICONSOLE_H_INCLUDED
