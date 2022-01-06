#include "main_frame.h"
#include "wxchoicelayer.h"
#include "builders/point_cmd.h"
#include "wx_binding.h"
#include <wx/artprov.h>
#include <wx/display.h>
#include <wx/msgdlg.h>

static const wxRect DEFAULT_WINDOW_SIZE = wxRect(0, 0, 1200, 800);

// Hotkeys
const char HOTKEY_COPY = 'C';
const char HOTKEY_PASTE = 'V';
const char HOTKEY_UNDO = 'Z';
const char HOTKEY_REDO = 'Y';

// Default buttons ids
const int MainFrame::ID_BTN_UNDO = wxNewId();
const int MainFrame::ID_BTN_REDO = wxNewId();

wxDEFINE_EVENT(wxCAD_PANEL_MOVE, MouseMoveEvent);

/*
typedef void (wxEvtHandler::*MouseMoveEventFunction)(MouseMoveEvent &);

#define MouseMoveEventHandler(func) wxEVENT_HANDLER_CAST(MouseMoveEventFunction, func)

#define EVT_CAD_MOUSE_MOVE(id, func) \
    wx__DECLARE_EVT1(wxCAD_PANEL_MOVE, id, MouseMoveEventHandler(func))

*/

wxBEGIN_EVENT_TABLE(MainFrame, wxFrame)
    EVT_COMMAND(wxID_ANY, wxEVT_COMMAND_TOOL_CLICKED, MainFrame::OnToolButtonClicked)
    EVT_CHAR_HOOK(MainFrame::OnKeyPressed)
    EVT_UPDATE_UI(wxID_ANY, MainFrame::OnUpdateHandler)
wxEND_EVENT_TABLE()



MainFrame::MainFrame(wxWindow* parent, wxWindowID id,
                     const wxString& title,
                     const wxPoint& pos,
                     const wxSize& size,
                     long style)
            : wxFrame(parent, id, title, pos, size, style)
{
    /*
	wxDisplay display(wxDisplay::GetFromWindow(this));
	this->SetSize(display.GetClientArea());
	*/
	this->SetSize(DEFAULT_WINDOW_SIZE);
	this->SetSizeHints(wxDefaultSize, wxDefaultSize);
	m_mgr.SetManagedWindow(this);
	m_mgr.SetFlags(wxAUI_MGR_DEFAULT);
    // Main menu bar
	CreateMenuBar();
    SetMenuBar(m_menu_bar);
    // Tool-bars
	m_mgr.AddPane(CreateNotebookDrawing(),
               wxAuiPaneInfo().Center().CaptionVisible(false)
               .Dock().Resizable().FloatingSize(wxDefaultSize));
    m_mgr.AddPane(CreateMainToolBar(),
                  wxAuiPaneInfo().Name(_T("main_toolbar")).ToolbarPane()
                  .Caption(_("menu")).Layer(10).Top().Gripper());
    // Initialize commands and tool-bars from kernel
    init_commands(dynamic_cast<wxFrame*>(this), &m_mgr, &m_cmd_dispatcher, &m_menu);
    // TODO
    // One panel mock
    m_panel2 = create_screen(drawing_container, this);
	drawing_container->AddPage(m_panel2, wxT("drawing"), false, wxNullBitmap);
	m_panel2->GetContext()->SetParentFrame(this);
	m_active_panel = m_panel2;
    // Append console input pane
	m_console = new UiConsole(this);
	m_console->SetSize(150, 150);
	m_mgr.AddPane(m_console,
            wxAuiPaneInfo().Name(_T("console"))
               .Caption(_("Console"))
               .Bottom());
	m_mgr.Update();
	this->Centre(wxBOTH);
    DefaultOperation("");
    m_message = "";
    // Status-bar
    m_status_bar = CreateStatusBar(4);
    Bind(wxCONSOLE_INPUT, &MainFrame::OnConsoleInputEvent, this);
    //Bind(wxCAD_PANEL_MOVE, &MainFrame::OnCadPanelMouseMove, this);
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
    //wxMessageBox("Input:" + event.GetInput());
    try
    {
        m_panel2->GetContext()->AssignInput(event.GetInput().ToStdString());
    }
    catch(const std::exception &e)
    {
        wxMessageBox(e.what());
    }

}

wxAuiToolBar* MainFrame::CreateMainToolBar()
{
    tool_main = new wxAuiToolBar(this, wxNewId(), wxDefaultPosition, wxDefaultSize, wxAUI_TB_DEFAULT_STYLE);
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
    m_message = msg;
}

void MainFrame::PrintCoordinates(double x, double y, double z)
{
    wxString coords;
    coords<<"x="<<x<<"  y="<<y;
    m_status_bar->SetStatusText(coords, 0);
}

void MainFrame::OnUpdateHandler(wxUpdateUIEvent& event)
{
    if (m_message != "")
    {
        m_console->SendText(m_message);
        m_message = "";
    }
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
    return drawing_container = new wxAuiNotebook(this, wxNewId(), wxDefaultPosition, wxDefaultSize, wxAUI_NB_DEFAULT_STYLE);
}

void MainFrame::OnKeyPressed(wxKeyEvent &event)
{
    bool processed = false;
    int code = event.GetKeyCode();

    // Hot key
    if(event.ControlDown())
    {
        HotKeyPressed(event);
        return;
    }

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

void MainFrame::HotKeyPressed(wxKeyEvent &event)
{
    Command *cmd = nullptr;
    int code = event.GetKeyCode();
    Context *context = m_panel2->GetContext();

    if(code==static_cast<int>(HOTKEY_COPY))
        cmd = m_cmd_dispatcher.GetCommand("copy", context);

    if(code==static_cast<int>(HOTKEY_PASTE))
        cmd = m_cmd_dispatcher.GetCommand("paste", context);

    if(code==static_cast<int>(HOTKEY_UNDO))
        context->Undo();

    if(code==static_cast<int>(HOTKEY_REDO))
        context->Redo();

    if(cmd)
        context->ExecuteCommand(cmd);
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
