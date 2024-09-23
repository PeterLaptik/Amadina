#ifndef COMMAND_PANEL_H_INCLUDED
#define COMMAND_PANEL_H_INCLUDED

#include <queue>
#include <wx/panel.h>
#include <wx/sizer.h>
#include <wx/textctrl.h>

class CommandPanel: public wxPanel
{
    public:
        CommandPanel(wxWindow *parent, wxWindowID id = wxID_ANY);
        ~CommandPanel() override = default;

        void InputText(const wxString &txt);

    private:
        void OnChar(wxKeyEvent& event);
        void SearchCommandByMask();

        std::queue<wxString> m_history;
        wxBoxSizer *m_main_sizer;
        wxTextCtrl *m_txt_input;
        wxTextCtrl *m_txt_history;

};

#endif // COMMAND_PANEL_H_INCLUDED
