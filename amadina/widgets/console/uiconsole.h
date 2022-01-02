#ifndef UICONSOLE_H_INCLUDED
#define UICONSOLE_H_INCLUDED

#include <wx/panel.h>
#include <array>

class wxTextCtrl;

static const char *CLASS_NAME_UI_CONSOLE = "UI console";

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

        void SendText(const wxString &txt, bool is_command = false);
        void ShowPrevious(void);
        void ShowNext(void);

    protected:
        //void OnInput(wxCommandEvent &event);
        void OnEnter(wxCommandEvent &event);

    private:
        inline void RefreshHistory(void);
        inline void AppendCommand(const wxString &cmd);
        inline void AppendMessage(const wxString &msg);
        // Finds position of a current input value
        // in a command log.
        // Helper for ShowPrevious / ShowNext methods
        inline int GetCurrentInputLogPosition(void);

        static const long INPUT_TEXT_ID;
        static const size_t COMMAND_LINE_HISTORY = 5;

        wxTextCtrl *m_input_line;
        wxTextCtrl *m_upper_lines;
        std::array<wxString,COMMAND_LINE_HISTORY> m_history_log;
        std::array<wxString,COMMAND_LINE_HISTORY> m_command_log;

        DECLARE_EVENT_TABLE()
};

#endif // UICONSOLE_H_INCLUDED
