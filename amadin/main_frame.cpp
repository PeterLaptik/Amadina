#include "main_frame.h"
#include "wxchoicelayer.h"
#include "../kernel/processor/default_commands.h"
#include "../kernel/builders/point_cmd.h"
//#include <wx/artprov.h>
#include <wx/display.h>
#include <wx/msgdlg.h>

static const wxRect DEFAULT_SIZE_RECT = wxRect(0, 0, 1200, 800);
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
	//this->SetSize(display.GetClientArea());
	this->SetSize(DEFAULT_SIZE_RECT);
	this->SetSizeHints(wxDefaultSize, wxDefaultSize);
	m_mgr.SetManagedWindow(this);
	m_mgr.SetFlags(wxAUI_MGR_DEFAULT);

	m_mgr.AddPane(CreateNotebookDrawing(), wxAuiPaneInfo().Center().CaptionVisible(false).Dock().Resizable().FloatingSize(wxDefaultSize));
    m_mgr.AddPane(CreateToolbarDraft(), wxAuiPaneInfo().Name(_T("toolbar_draft")).ToolbarPane().Caption(_("drawing")).Layer(10).Top().Gripper());
    m_mgr.AddPane(CreateToolbarSnap(), wxAuiPaneInfo().Name(_T("toolbar_snap")).ToolbarPane().Caption(_("drawing")).Layer(10).Top().Gripper());
    m_mgr.AddPane(CreateToolbarLayer(), wxAuiPaneInfo().Name(_T("toolbar_layer")).ToolbarPane().Caption(_("drawing")).Layer(10).Top().Gripper());


    ViewPanel *m_panel2 = new ViewPanel(drawing_container);
	drawing_container->AddPage(m_panel2, wxT("drawing"), false, wxNullBitmap);
	m_active_panel = m_panel2;



	m_console = new UiConsole(this);
	m_console->SetSize(150, 150);
	m_mgr.AddPane(m_console,
            wxAuiPaneInfo().Name(_T("console"))
               .Caption(_("Console"))
               .Bottom());



    CreateMenuBar();
    SetMenuBar(m_menu_bar);


	m_mgr.Update();
	this->Centre(wxBOTH);

    cad::command::RegisterDefaultCommands(m_interpreter);
    m_interpreter.SetActivePanel(m_panel2);

    CommandMock();

    Bind(wxCONSOLE_INPUT, &MainFrame::OnConsoleInputEvent, this);
//    Connect(wxID_ANY, wxEVT_COMMAND_MENU_SELECTED,
//      wxCommandEventHandler(MainFrame::OnMenuClicked));
}


MainFrame::~MainFrame()
{
	m_mgr.UnInit();
}


void MainFrame::CreateMenuBar()
{
    // Create default menus
    m_menu_bar = new wxMenuBar();
    wxMenu *m_menu_file = new wxMenu();
    wxMenu *m_menu_edit = new wxMenu();
    wxMenu *m_menu_view = new wxMenu();
    wxMenu *m_menu_draw = new wxMenu();
    wxMenu *m_menu_settings = new wxMenu();
    wxMenu *m_menu_about = new wxMenu();
    // Initialize external holders
    AmadinaMenuList *menu_list = m_menu.GetMenuList();
    menu_list->menu_file = m_menu_file;
    menu_list->menu_edit = m_menu_edit;
    menu_list->menu_view = m_menu_view;
    menu_list->menu_draw = m_menu_draw;
    menu_list->menu_settings = m_menu_settings;
    menu_list->menu_about = m_menu_about;
    // Fill menu bar
    m_menu_bar->Append(m_menu_file, _T("File"));
    m_menu_bar->Append(m_menu_edit, _T("Edit"));
    m_menu_bar->Append(m_menu_view, _T("View"));
    m_menu_bar->Append(m_menu_draw, _T("Draw"));
    m_menu_bar->Append(m_menu_settings, _T("Settings"));
    m_menu_bar->Append(m_menu_about, _T("About"));
    // Test
    m_menu_settings->Append(1105, "xx");

}

void MainFrame::OnMenuClicked(wxCommandEvent &event)
{
    wxString command = "Command:";
    command<<event.GetId();
    wxMessageBox(command);
}

// Processes console input
void MainFrame::OnConsoleInputEvent(wxEventConsoleInput &event)
{
    wxMessageBox("Input:" + event.GetInput());
}

wxAuiToolBar* MainFrame::CreateToolbarDraft()
{
    int cmd_id;
    std::string cmd_name;

    tool_draft = new wxAuiToolBar(this, ID_TOOL_DRAFT, wxDefaultPosition, wxDefaultSize, wxAUI_TB_DEFAULT_STYLE);

    cmd_id = wxNewId();
    cmd_name = cad::command::CMD_POINT;
    tool_draft->AddTool(cmd_id, cmd_name, wxBitmap(wxImage(_T("res\\icons\\icon_point.ico"))),
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

wxAuiToolBar* MainFrame::CreateToolbarLayer()
{
    tool_layer = new wxAuiToolBar(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxAUI_TB_DEFAULT_STYLE | wxAUI_TB_HORIZONTAL);
    tool_layer->AddTool(wxID_ANY, "aaa", wxBitmap(wxImage(_T("res\\icons\\icon_layers.ico"))),
                        wxNullBitmap, wxITEM_NORMAL, _("Show grid"), wxEmptyString, NULL);

    tool_layer->AddSeparator();
    wxChoiceLayer *choice = new wxChoiceLayer(tool_layer, wxNewId());
    choice->SetReadOnly();
    std::vector<Layer> layers;
    Layer l1("name1");
    Layer l2("name2", Colour::BLUE);
    Layer l3("name3", Colour::GREEN);
    layers.push_back(l1);
    layers.push_back(l2);
    layers.push_back(l3);
    choice->AddLayers(layers);

    tool_layer->AddControl(choice);
    tool_layer->AddSeparator();
    return tool_layer;
}

void MainFrame::CommandMock()
{
    m_cmd_dispatcher.RegisterCommand(new CmdPoint(), "point");
    long id = m_menu.AppendMenuCommand("Point", "point", ui::CMD_DRAW);
    m_cmd_dispatcher.RegisterHandler(id, "point");

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
        m_interpreter.ExecuteCommand(cad::command::CMD_CANCEL);
        break;
    case WXK_DELETE:
        m_interpreter.ExecuteCommand(cad::command::CMD_DELETE);
        break;
    }

    wxWindow *win = wxWindow::FindFocus();
    //win->GetParent();
    wxString f = "focus:";
    f<<win->GetName();
    f<<"<-"<<win->GetParent()->GetName();
    event.Skip();
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
    if(toolbar)
        cmd = toolbar->FindTool(event.GetId())->GetLabel();

    Command *xx = m_cmd_dispatcher.GetCommand(event.GetId());

    wxString tmp = "cmd:";
    tmp<<(xx==nullptr);
    wxMessageBox(tmp);
    //m_interpreter.ExecuteCommand(cmd.ToStdString());
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
