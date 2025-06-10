#ifndef MAIN_FRAME_H_INCLUDED
#define MAIN_FRAME_H_INCLUDED

#include "application.h"
#include "command_panel.h"
#include <wx/frame.h>
#include <wx/aui/aui.h>
#include <string>
#include <memory>
#include <map>

const wxSize DEFAULT_WINDOW_SIZE = wxSize(800,600);

namespace cad::command
{
    class ApplicationContext;
}

//class wxRibbonBar;
class wxRibbonButtonBar;
class wxRibbonButtonBarEvent;
class wxAbstractModeller;
class wxSplitterWindow;
class wxAuiNotebook;
class ARibbon;

class MainFrame: public wxFrame, public Application
{
    public:
        MainFrame(wxWindow* parent,
                  wxWindowID id = wxID_ANY,
                  const wxString& title = wxEmptyString,
                  const wxPoint& pos = wxDefaultPosition,
                  const wxSize& size = DEFAULT_WINDOW_SIZE,
                  long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL);

        virtual ~MainFrame();

        cad::command::ApplicationContext* GetAppContext() override;

    protected:
        /// Definition of a system commands handler.
        /// Regular system commands are not inherited from a CommandAbstract,
        /// and are not kept as a prototypes in a dispatcher.
        /// Invocation of system command means call of a 'MainFrame' appropriate method.
        typedef void (MainFrame::*CommandHandler)(wxEvent&);

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

        // Advanced user interface mgr
		wxAuiManager m_mgr;

		// All widgets (including a ribbon bar) are situated
		// on the following panel
		wxPanel *m_main_panel;

		// Main sizer: vertical
		wxBoxSizer* m_main_sizer;

        // Command line
        CommandPanel *m_cmd_panel;

        ARibbon *m_ribbon;
		wxAuiNotebook *m_notebook;
		wxStatusBar *m_status_bar;
		wxAbstractModeller *m_modeller;
        wxSplitterWindow *m_splitter;

    private:
        void SketchModeHandler(wxEvent &event);
        wxRibbonButtonBar *m_ribbonButtonBar6;

        cad::command::ApplicationContext *m_app_context;
        std::map<wxWindowID, std::string> m_commands_buttons_map;
        std::map<wxWindowID,CommandHandler> m_system_commands_map;

        void RibbonInit(void);

    DECLARE_EVENT_TABLE()
};

#endif // MAIN_FRAME_H_INCLUDED
