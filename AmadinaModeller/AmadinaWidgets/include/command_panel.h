#ifndef COMMAND_PANEL_H_INCLUDED
#define COMMAND_PANEL_H_INCLUDED

#include <vector>
#include <memory>
#include <wx/panel.h>
#include <wx/sizer.h>
#include <wx/textctrl.h>

class CommandAutocompliter;

class CommandPanel: public wxPanel
{
    public:
        CommandPanel(wxWindow *parent, wxWindowID id = wxID_ANY);
        ~CommandPanel() override = default;

        void InputText(const wxString &txt);
        void SetAutocompleteList(const std::vector<std::string> *list);

    private:
        void OnChar(wxKeyEvent& event);
        void DeleteHistoryTopLine();
        void ProposeCommandByFirstChars();

        std::unique_ptr<CommandAutocompliter> m_autocompleter;
        wxTextCtrl *m_txt_input;
        wxTextCtrl *m_txt_history;

};

#endif // COMMAND_PANEL_H_INCLUDED
