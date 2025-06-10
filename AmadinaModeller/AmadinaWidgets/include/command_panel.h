#ifndef COMMAND_PANEL_H_INCLUDED
#define COMMAND_PANEL_H_INCLUDED

#include "command_autocompleter.h"
#include "sheet_context.h"
#include <vector>
#include <deque>
#include <wx/panel.h>
#include <wx/sizer.h>
#include <wx/textctrl.h>

#ifdef _WINDLL
#define DLL_EXPORT __declspec(dllexport)
#else
#define DLL_EXPORT
#endif

using cad::app::SheetContext;

///\brief Composite widget for command input
/// Contains: command line text input and separate multiline text box for previous input commands (history text box)
class CommandPanel: public wxPanel
{
    public:
        DLL_EXPORT CommandPanel(wxWindow *parent, wxWindowID id = wxID_ANY);
        DLL_EXPORT ~CommandPanel() override = default;

        DLL_EXPORT void SetContext(SheetContext *ctx);

        /// Sends input command to a history textbox and context.
        ///\param txt - command
        DLL_EXPORT void InputCommand(const wxString &txt);

        /// Shows message in a panel
        ///\param message - message text
        DLL_EXPORT void SendMessage(const wxString &txt);

        /// Assign command list for an autocomplete util.
        /// Works if tab-key is pressed during the input (for the first word token only)
        ///\param list - sorted list of accessible commands names
        DLL_EXPORT void SetAutocompleteList(const std::vector<std::string> *list);

    private:
        void OnChar(wxKeyEvent& event);
        void DeleteHistoryTopLine();
        void ProposeCommandByFirstChars();
        void ExtractHistoryLine(int key_code);

        SheetContext *m_sheet_context;

        CommandAutocompleter m_autocompleter;
        std::deque<std::string> m_cmd_history;
        int m_cmd_history_cursor = -1;

        wxTextCtrl *m_txt_input;
        wxTextCtrl *m_txt_history;
};

#endif // COMMAND_PANEL_H_INCLUDED
