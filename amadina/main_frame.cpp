#include "main_frame.h"
#include "wxchoicelayer.h"
#include "builders/point_cmd.h"
#include "wx_binding.h"
#include <wx/artprov.h>
#include <wx/display.h>
#include <wx/msgdlg.h>

static const wxRect DEFAULT_SIZE_RECT = wxRect(0, 0, 1200, 800);
//static const wxSize DEFAULT_BUTTON_SIZE = wxSize(32, 32);

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
const int MainFrame::ID_BTN_UNDO = wxNewId();
const int MainFrame::ID_BTN_REDO = wxNewId();

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

	CreateMenuBar();
    SetMenuBar(m_menu_bar);

	m_mgr.AddPane(CreateNotebookDrawing(), wxAuiPaneInfo().Center().CaptionVisible(false).Dock().Resizable().FloatingSize(wxDefaultSize));
    m_mgr.AddPane(CreateMainToolBar(), wxAuiPaneInfo().Name(_T("main_toolbar")).ToolbarPane().Caption(_("menu")).Layer(10).Top().Gripper());
    //m_mgr.AddPane(CreateToolbarSnap(), wxAuiPaneInfo().Name(_T("toolbar_snap")).ToolbarPane().Caption(_("drawing")).Layer(10).Top().Gripper());
//    m_mgr.AddPane(CreateToolbarLayer(), wxAuiPaneInfo().Name(_T("toolbar_layer")).ToolbarPane().Caption(_("drawing")).Layer(10).Top().Gripper());
    init_commands(dynamic_cast<wxFrame*>(this), &m_mgr, &m_cmd_dispatcher, &m_menu);

    m_panel2 = new ViewPanel(drawing_container);
	drawing_container->AddPage(m_panel2, wxT("drawing"), false, wxNullBitmap);
	m_active_panel = m_panel2;
	m_panel2->GetContext()->SetParentFrame(this);

    // Append console input pane
	m_console = new UiConsole(this);
	m_console->SetSize(150, 150);
	m_mgr.AddPane(m_console,
            wxAuiPaneInfo().Name(_T("console"))
               .Caption(_("Console"))
               .Bottom());



	m_mgr.Update();
	this->Centre(wxBOTH);


	Context::AssignCommandDispatcher(&m_cmd_dispatcher);

//    cad::command::RegisterDefaultCommands(m_interpreter);
    //m_interpreter.SetActivePanel(m_panel2);

//    CommandMock();

    DefaultOperation("");
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

wxAuiToolBar* MainFrame::CreateMainToolBar()
{
    tool_main = new wxAuiToolBar(this, ID_TOOL_SNAP, wxDefaultPosition, wxDefaultSize, wxAUI_TB_DEFAULT_STYLE);
    tool_main->AddTool(wxNewId(), wxT("save"), wxArtProvider::GetBitmap(wxART_FILE_SAVE),
                        wxNullBitmap, wxITEM_NORMAL, _("Show grid"), wxEmptyString, NULL);
    tool_main->AddTool(ID_BTN_UNDO, wxT("undo"), wxArtProvider::GetBitmap(wxART_UNDO),
                        wxNullBitmap, wxITEM_NORMAL, _("Show grid"), wxEmptyString, NULL);
    tool_main->AddTool(ID_BTN_REDO, wxT("redo"), wxArtProvider::GetBitmap(wxART_REDO),
                        wxNullBitmap, wxITEM_NORMAL, _("Show grid"), wxEmptyString, NULL);
    return tool_main;
}

void MainFrame::DefaultOperation(const wxString &name)
{
    bool undo;
    bool redo;
    Context *context = m_panel2->GetContext();
    context->TerminateCommand();

    // Undo / redo
    if(name=="undo")
    {
        context->Undo();
    }
    else if(name=="redo")
    {
        context->Redo();
    }


    context->GetUndoRedoState(undo, redo);
    tool_main->EnableTool(ID_BTN_UNDO, undo);
    tool_main->EnableTool(ID_BTN_REDO, redo);
}

void MainFrame::SetUndoRedoState(bool can_undo, bool can_redo)
{
    bool undo;
    bool redo;
    Context *context = m_panel2->GetContext();
    context->GetUndoRedoState(undo, redo);
    tool_main->EnableTool(ID_BTN_UNDO, undo);
    tool_main->EnableTool(ID_BTN_REDO, redo);
    tool_main->Refresh();
}

void MainFrame::PrintMessage(const std::string &msg)
{
    m_console->SendText(msg);
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
    Layer l2("name2", Colours::BLUE);
    Layer l3("name3", Colours::GREEN);
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
    m_cmd_dispatcher.RegisterCommand(new CmdPoint(m_panel2->GetContext()), "point");
    long id = m_menu.AppendMenuCommand("Point", "point", ui::CMD_DRAW);
    m_cmd_dispatcher.RegisterHandler(id, "point");

}

wxAuiNotebook* MainFrame::CreateNotebookDrawing()
{
    return drawing_container = new wxAuiNotebook(this, ID_NOTEBOOK, wxDefaultPosition, wxDefaultSize, wxAUI_NB_DEFAULT_STYLE);
}

void MainFrame::OnKeyPressed(wxKeyEvent &event)
{
    bool processed = false;
    int code = event.GetKeyCode();
    switch(code)
    {
        case WXK_RETURN:
        case WXK_NUMPAD_ENTER:
            m_panel2->ScreenKeyPressed(WXK_RETURN);
            m_panel2->RefreshScreen();
            break;
        case WXK_ESCAPE:
            // Cancel screen selection
            m_panel2->ClearSelection();
            m_panel2->GetContext()->TerminateCommand();
            // TODO
            // May be extra-call. Depends on wx-version and compiller
            m_panel2->RefreshScreen();
            processed = true; // ignore ESC for console input
            break;
        case WXK_UP:
            m_console->ShowPrevious();
            break;
        case WXK_DOWN:
            m_console->ShowNext();
            break;
        case WXK_DELETE:
            Context *context = m_panel2->GetContext();
            Command *cmd = m_cmd_dispatcher.GetCommand("delete", context);
            if(cmd)
                context->ExecuteCommand(cmd);
            break;
    }

    // Send to console
    if(!processed)
        event.Skip();
}

void MainFrame::OnToolButtonClicked(wxCommandEvent &event)
{
    int tool_id = event.GetId();
    wxObject *obj = event.GetEventObject();
    // Process sticky buttons (preferences, variables etc.)
    if(obj==tool_snap)
    {
        OnStickyButtonClicked(event);
        return;
    }

    if(obj==tool_main)
    {
        wxAuiToolBarItem *item = tool_main->FindTool(tool_id);
        if(item)
            DefaultOperation(item->GetLabel());
        return;
    }

    // Start executing regular command
    Context *context = m_panel2->GetContext();
    Command *cmd = m_cmd_dispatcher.GetCommand(tool_id, context);
    if(cmd)
    {
        m_console->SendText(m_cmd_dispatcher.GetCommandName(tool_id), true);
        context->ExecuteCommand(cmd);
    }
}

void MainFrame::OnStickyButtonClicked(wxCommandEvent &event)
{
    wxString cmd;
    wxAuiToolBarItem *item = tool_snap->FindTool(event.GetId());
    if(!item)
        return;

    item->SetSticky(!item->IsSticky());
    cmd<<item->GetLabel()<<" "<<item->IsSticky();
    //m_interpreter.ExecuteCommand(cmd.ToStdString());
    this->Refresh();
}
