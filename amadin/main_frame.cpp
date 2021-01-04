#include "main_frame.h"
#include "../kernel/processor/default_commands.h"
//#include <wx/artprov.h>
#include <wx/display.h>
#include <wx/msgdlg.h>

static const wxRect DEFAULT_SIZE_RECT = wxRect(0, 0, 800, 600);
static const wxSize DEFAULT_BUTTON_SIZE = wxSize(32, 32);

const int MainFrame::ID_TOOL_DRAFT = wxNewId();
const int MainFrame::ID_TOOL_SNAP = wxNewId();
const int MainFrame::ID_BTN_DRAW_POINT = wxNewId();
const int MainFrame::ID_BTN_DRAW_LINE = wxNewId();
const int MainFrame::ID_BTN_DRAW_LINE_ORTHO = wxNewId();
const int MainFrame::ID_BTN_DRAW_CIRCLE = wxNewId();
const int MainFrame::ID_BTN_DRAW_SQUARE_CENTER = wxNewId();
const int MainFrame::ID_BTN_DRAW_SQUARE_POINTS = wxNewId();
const int MainFrame::ID_BTN_SNAP_GRID_SHOW = wxNewId();
const int MainFrame::ID_BTN_SNAP_GRID = wxNewId();
const int MainFrame::ID_BTN_SNAP_POINT = wxNewId();
const int MainFrame::ID_BTN_SNAP_CENTER = wxNewId();
const int MainFrame::ID_BTN_SNAP_ORTHO = wxNewId();
const int MainFrame::ID_BTN_SNAP_INTERSECTION = wxNewId();
const int MainFrame::ID_BTN_SNAP_TANGENT = wxNewId();
const int MainFrame::ID_BTN_SNAP_ANGLE = wxNewId();
const int MainFrame::ID_NOTEBOOK = wxNewId();

wxBEGIN_EVENT_TABLE(MainFrame, wxFrame)
    EVT_COMMAND(wxID_ANY, wxEVT_COMMAND_TOOL_CLICKED, MainFrame::OnToolButtonClicked)
    EVT_CHAR_HOOK(MainFrame::OnKeyPressed)
wxEND_EVENT_TABLE()


MainFrame::MainFrame(wxWindow* parent, wxWindowID id,
                     const wxString& title,
                     const wxPoint& pos,
                     const wxSize& size,
                     long style)
            : wxFrame(parent, id, title, pos, size, style)
{
	wxDisplay display(wxDisplay::GetFromWindow(this));
	this->SetSize(display.GetClientArea());
	this->SetSize(DEFAULT_SIZE_RECT);
	this->SetSizeHints(wxDefaultSize, wxDefaultSize);
	m_mgr.SetManagedWindow(this);
	m_mgr.SetFlags(wxAUI_MGR_DEFAULT);

	m_mgr.AddPane(CreateNotebookDrawing(), wxAuiPaneInfo().Center().CaptionVisible(false).Dock().Resizable().FloatingSize(wxDefaultSize));
    m_mgr.AddPane(CreateToolbarDraft(), wxAuiPaneInfo().Name(_T("toolbar_draft")).ToolbarPane().Caption(_("drawing")).Layer(10).Top().Gripper());
    m_mgr.AddPane(CreateToolbarSnap(), wxAuiPaneInfo().Name(_T("toolbar_snap")).ToolbarPane().Caption(_("drawing")).Layer(10).Top().Gripper());

    ViewPanel *m_panel2 = new ViewPanel(drawing_container);
	drawing_container->AddPage(m_panel2, wxT("drawing"), false, wxNullBitmap);
	m_active_panel = m_panel2;

	m_mgr.Update();
	this->Centre(wxBOTH);

    cad::command::RegisterDefaultCommands(m_interpreter);
    m_interpreter.SetActivePanel(m_panel2);
}


MainFrame::~MainFrame()
{
	m_mgr.UnInit();
}


wxAuiToolBar* MainFrame::CreateToolbarDraft()
{
    tool_draft = new wxAuiToolBar(this, ID_TOOL_DRAFT, wxDefaultPosition, wxDefaultSize, wxAUI_TB_DEFAULT_STYLE);
    tool_draft->AddTool(ID_BTN_DRAW_POINT, cad::command::CMD_POINT, wxBitmap(wxImage(_T("res\\icons\\icon_point.ico"))),
                        wxNullBitmap, wxITEM_NORMAL, _("Plot point"), wxEmptyString, NULL);
    tool_draft->AddTool(ID_BTN_DRAW_LINE, cad::command::CMD_LINE, wxBitmap(wxImage(_T("res\\icons\\icon_line.ico"))),
                        wxNullBitmap, wxITEM_NORMAL, _("Draw line"), wxEmptyString, NULL);
    tool_draft->AddTool(ID_BTN_DRAW_LINE_ORTHO, cad::command::CMD_LINE_ORTHOGONAL, wxBitmap(wxImage(_T("res\\icons\\icon_line_ortho.ico"))),
                        wxNullBitmap, wxITEM_NORMAL, _("Draw line orthogonal"), wxEmptyString, NULL);
    tool_draft->AddTool(ID_BTN_DRAW_CIRCLE, cad::command::CMD_CIRCLE, wxBitmap(wxImage(_T("res\\icons\\icon_circle.ico"))),
                        wxNullBitmap, wxITEM_NORMAL, _("Draw circle"), wxEmptyString, NULL);
    tool_draft->AddTool(ID_BTN_DRAW_SQUARE_CENTER, cad::command::CMD_SQUARE_CENTER, wxBitmap(wxImage(_T("res\\icons\\icon_square.ico"))),
                        wxNullBitmap, wxITEM_NORMAL, _("Draw square from center"), wxEmptyString, NULL);
    tool_draft->AddTool(ID_BTN_DRAW_SQUARE_POINTS, cad::command::CMD_SQUARE, wxBitmap(wxImage(_T("res\\icons\\icon_square_pt.ico"))),
                        wxNullBitmap, wxITEM_NORMAL, _("Draw square"), wxEmptyString, NULL);
    tool_draft->Realize();
    return tool_draft;
}

wxAuiToolBar* MainFrame::CreateToolbarSnap()
{
    tool_snap = new wxAuiToolBar(this, ID_TOOL_SNAP, wxDefaultPosition, wxDefaultSize, wxAUI_TB_DEFAULT_STYLE);
    (tool_snap->AddTool(ID_BTN_SNAP_GRID_SHOW, cad::preferences::PREF_GRID_SHOW, wxBitmap(wxImage(_T("res\\icons\\icon_grid.ico"))),
                        wxNullBitmap, wxITEM_NORMAL, _("Show grid"), wxEmptyString, NULL))->SetSticky(true);
    (tool_snap->AddTool(ID_BTN_SNAP_GRID, cad::preferences::PREF_SNAP_GRID, wxBitmap(wxImage(_T("res\\icons\\icon_snap_grid.ico"))),
                        wxNullBitmap, wxITEM_NORMAL, _("Snap grid"), wxEmptyString, NULL))->SetSticky(false);
    (tool_snap->AddTool(ID_BTN_SNAP_POINT, cad::preferences::PREF_SNAP_POINT, wxBitmap(wxImage(_T("res\\icons\\icon_snap_point.ico"))),
                        wxNullBitmap, wxITEM_NORMAL, _("Snap point"), wxEmptyString, NULL))->SetSticky(true);
    (tool_snap->AddTool(ID_BTN_SNAP_CENTER, cad::preferences::PREF_SNAP_CENTER, wxBitmap(wxImage(_T("res\\icons\\icon_snap_center.ico"))),
                        wxNullBitmap, wxITEM_NORMAL, _("Snap center"), wxEmptyString, NULL))->SetSticky(true);
    (tool_snap->AddTool(ID_BTN_SNAP_INTERSECTION, cad::preferences::PREF_SNAP_INTERSECTION, wxBitmap(wxImage(_T("res\\icons\\icon_snap_intersection.ico"))),
                        wxNullBitmap, wxITEM_NORMAL, _("Snap intersection"), wxEmptyString, NULL))->SetSticky(true);
    (tool_snap->AddTool(ID_BTN_SNAP_ORTHO, cad::preferences::PREF_SNAP_ORTHO, wxBitmap(wxImage(_T("res\\icons\\icon_snap_ortho.ico"))),
                        wxNullBitmap, wxITEM_NORMAL, _("Snap orthogonal"), wxEmptyString, NULL))->SetSticky(true);
    (tool_snap->AddTool(ID_BTN_SNAP_TANGENT, cad::preferences::PREF_SNAP_TANGENT, wxBitmap(wxImage(_T("res\\icons\\icon_snap_tangent.ico"))),
                        wxNullBitmap, wxITEM_NORMAL, _("Snap tangent"), wxEmptyString, NULL))->SetSticky(true);
    (tool_snap->AddTool(ID_BTN_SNAP_ANGLE, cad::preferences::PREF_SNAP_ANGLE, wxBitmap(wxImage(_T("res\\icons\\icon_snap_angle.ico"))),
                        wxNullBitmap, wxITEM_NORMAL, _("Snap angle"), wxEmptyString, NULL))->SetSticky(true);
    return tool_snap;
}

wxAuiNotebook* MainFrame::CreateNotebookDrawing()
{
    return drawing_container = new wxAuiNotebook(this, ID_NOTEBOOK, wxDefaultPosition, wxDefaultSize, wxAUI_NB_DEFAULT_STYLE);
}

void MainFrame::OnKeyPressed(wxKeyEvent &event)
{
    int code = event.GetKeyCode();
    switch(code)
    {
    case WXK_ESCAPE:
        m_active_panel->CancelCommand();
        break;
    }
}

void MainFrame::OnToolButtonClicked(wxCommandEvent &event)
{
    wxString cmd;
    int button_id = event.GetId();
    wxObject *obj = event.GetEventObject();
    // Process sticky buttons (preferences, variables etc.)
    if(obj==tool_snap)
    {
        OnStickyButtonClicked(event);
        return;
    }
    // Process command buttons
    // Each command is being kept in tool-item label
    wxAuiToolBar *toolbar = dynamic_cast<wxAuiToolBar*>(obj);
    if(obj)
        cmd = toolbar->FindTool(event.GetId())->GetLabel();

    m_interpreter.ExecuteCommand(cmd.ToStdString());
}

void MainFrame::OnStickyButtonClicked(wxCommandEvent &event)
{
    wxString cmd;
    wxAuiToolBarItem *item = tool_snap->FindTool(event.GetId());
    if(!item)
        return;

    item->SetSticky(!item->IsSticky());
    cmd<<item->GetLabel()<<" "<<item->IsSticky();
    m_interpreter.ExecuteCommand(cmd.ToStdString());
    this->Refresh();
}
