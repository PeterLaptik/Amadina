#ifndef MAIN_FRAME_H_INCLUDED
#define MAIN_FRAME_H_INCLUDED

#include "command_dispatcher.h"
#include <wx/aui/aui.h>
#include <memory>
#include <map>

using cad::modeller::CommandDispatcher;

const wxSize DEFAULT_WINDOW_SIZE = wxSize(800,600);

class wxRibbonBar;
class wxRibbonButtonBar;
class wxRibbonButtonBarEvent;
class wxModeller3D;

class MainFrame: public wxFrame
{
    public:
        MainFrame(wxWindow* parent,
                  wxWindowID id = wxID_ANY,
                  const wxString& title = wxEmptyString,
                  const wxPoint& pos = wxDefaultPosition,
                  const wxSize& size = DEFAULT_WINDOW_SIZE,
                  long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL);

        virtual ~MainFrame();

    protected:
        /// Definition of a system commands handler.
        /// Regular system commands are not inherited from a CommandAbstract,
        /// and are not kept as a prototypes in a dispatcher.
        /// Invocation of system command means call of a 'MainFrame' appropriate method.
        typedef void (MainFrame::*CommandHandler)(wxWindowID);
        /// System commands registrar (handler-method is passed)
        void AddSystemCommand(wxRibbonButtonBar *bar, const wxString &label,
                              const wxBitmap &bitmap, const wxString &help,
                              bool is_toggle, CommandHandler handler);
        /// Regular commands registrar
        void AddButtonCommand(wxRibbonButtonBar *bar, const wxString &label,
                              const wxBitmap &bitmap, const wxString &help,
                              const std::string &name);
        /// Regular commands handler
        void OnButtonClicked(wxRibbonButtonBarEvent &event);
		wxAuiManager m_mgr;

		// All widgets (including a ribbon bar) are situated
		// on the following panel
		wxPanel *m_main_panel;

		// Main sizer: vertical
		wxBoxSizer* m_main_sizer;

		wxRibbonBar *m_ribbon;
		wxAuiNotebook *m_notebook;
		wxStatusBar *m_status_bar;
		wxModeller3D *m_modeller;

    private:
        void SketchModeHandler(wxWindowID button_id);

        std::map<wxWindowID, std::string> m_commands_buttons_map;
        std::map<wxWindowID,CommandHandler> m_system_commands_map;

        void RibbonInit(void);

    DECLARE_EVENT_TABLE()
};

#endif // MAIN_FRAME_H_INCLUDED
