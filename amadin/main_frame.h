#ifndef MAIN_FRAME_H_INCLUDED
#define MAIN_FRAME_H_INCLUDED

#include "../kernel/view_2d/viewpanel.h"
#include "../kernel/processor/interpreter.h"
#include "../kernel/context/context.h"
#include "widgets/console/uiconsole.h"
#include "events/events.h"
#include <wx/aui/aui.h>
#include <map>


static const wxSize MAIN_FRAME_DEFAULT_SIZE = wxSize(640, 480);


class MainFrame : public wxFrame
{
    public:
		MainFrame(wxWindow* parent,
            wxWindowID id = wxID_ANY,
            const wxString& title = wxT("Amadin drafter"),
            const wxPoint& pos = wxDefaultPosition,
            const wxSize& size = MAIN_FRAME_DEFAULT_SIZE,
            long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL);
		virtual ~MainFrame();



	protected:
	    void OnToolButtonClicked(wxCommandEvent &event);
	    void OnStickyButtonClicked(wxCommandEvent &event);
	    void OnKeyPressed(wxKeyEvent &event);
	    void OnConsoleInputEvent(wxEventConsoleInput &event);
	    void OnMenuClicked(wxCommandEvent &event);
	    void CreateMenuBar(void);

	    CommandInterpreter m_interpreter;
	    ViewPanel *m_active_panel;


	private:
	    wxAuiToolBar* CreateToolbarDraft(void);
	    wxAuiToolBar* CreateToolbarSnap(void);
	    wxAuiToolBar* CreateToolbarLayer(void);
	    wxAuiNotebook* CreateNotebookDrawing(void);

	    // Controls ids
	    static const int ID_NOTEBOOK;
	    static const int ID_TOOL_DRAFT;
	    static const int ID_TOOL_SNAP;
	    static const int ID_BTN_DRAW_POINT;
	    static const int ID_BTN_DRAW_LINE;
	    static const int ID_BTN_DRAW_LINE_ORTHO;
	    static const int ID_BTN_DRAW_CIRCLE;
	    static const int ID_BTN_DRAW_SQUARE_CENTER;
	    static const int ID_BTN_DRAW_SQUARE_POINTS;
        static const int ID_BTN_SNAP_GRID_SHOW;
        static const int ID_BTN_SNAP_GRID;
        static const int ID_BTN_SNAP_POINT;
        static const int ID_BTN_SNAP_CENTER;
        static const int ID_BTN_SNAP_INTERSECTION;
        static const int ID_BTN_SNAP_ORTHO;
        static const int ID_BTN_SNAP_TANGENT;
        static const int ID_BTN_SNAP_ANGLE;

        wxAuiManager m_mgr;
        wxAuiToolBar *tool_draft;
        wxAuiToolBar *tool_snap;
        wxAuiToolBar *tool_layer;
        wxAuiNotebook *drawing_container;

        wxMenuBar *m_menu_bar;
        UiConsole *m_console;

        std::map<ViewPanel*,Context*> m_context_map;

        DECLARE_EVENT_TABLE()
};

#endif // MAIN_FRAME_H_INCLUDED
