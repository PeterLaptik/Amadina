#ifndef MAIN_FRAME_H_INCLUDED
#define MAIN_FRAME_H_INCLUDED

//#include "../kernel/view_2d/viewpanel.h"
//#include "../kernel/processor/interpreter.h"
#include "command/dispatcher.h"
#include "menu/menu.h"
#include "widgets/console/uiconsole.h"
#include "events/events.h"
#include <wx/aui/aui.h>
#include <map>
#include "../wx_binding/classes/viewpanel.h"
#include "context/callable.h"


static const wxSize MAIN_FRAME_DEFAULT_SIZE = wxSize(640, 480);


class MainFrame : public wxFrame, public CallableFrame
{
    public:
		MainFrame(wxWindow* parent,
            wxWindowID id = wxID_ANY,
            const wxString& title = wxT("Amadina drafter"),
            const wxPoint& pos = wxDefaultPosition,
            const wxSize& size = MAIN_FRAME_DEFAULT_SIZE,
            long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL);
		virtual ~MainFrame();

		virtual void SetUndoRedoState(bool can_undo, bool can_redo);
		virtual void PrintMessage(const std::string &msg) override;


	protected:
	    void OnToolButtonClicked(wxCommandEvent &event);
	    void OnStickyButtonClicked(wxCommandEvent &event);
	    void OnKeyPressed(wxKeyEvent &event);
	    void HotKeyPressed(wxKeyEvent &event);
	    void OnConsoleInputEvent(wxEventConsoleInput &event);
	    void OnMenuClicked(wxCommandEvent &event);
	    // Creates main menu sections
	    inline void CreateMenuBar(void);

	    //CommandInterpreter m_interpreter;
	    ViewPanel *m_active_panel;


	private:
	    wxAuiToolBar* CreateToolbarLayer(void);
	    wxAuiNotebook* CreateNotebookDrawing(void);
	    wxAuiToolBar* CreateMainToolBar(void);
	    void DefaultOperation(const wxString &name);

	    // // Default buttons ids
        static const int ID_BTN_UNDO;
        static const int ID_BTN_REDO;

        void CommandMock(void);

        wxAuiManager m_mgr;
        wxAuiToolBar *tool_main;
        wxAuiToolBar *tool_draft;
        wxAuiToolBar *tool_snap;
        wxAuiToolBar *tool_layer;
        wxAuiNotebook *drawing_container;

        wxMenuBar *m_menu_bar;
        UiConsole *m_console;

        ViewPanel *m_panel2;

        AmadinaMenu m_menu;
        CommandDispatcher m_cmd_dispatcher;

        DECLARE_EVENT_TABLE()
};

#endif // MAIN_FRAME_H_INCLUDED
