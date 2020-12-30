#include "main_frame.h"
#include "../kernel/processor/default_commands.h"
#include <wx/artprov.h>

static const wxSize DEFAULT_BUTTON_SIZE = wxSize(32, 32);

const int MainFrame::ID_TOOL_DRAFT = wxNewId();
const int MainFrame::ID_BTN_DRAW_POINT = wxNewId();
const int MainFrame::ID_BTN_DRAW_LINE = wxNewId();
const int MainFrame::ID_BTN_DRAW_CIRCLE = wxNewId();
const int MainFrame::ID_BTN_DRAW_SQUARE = wxNewId();
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
	this->SetSizeHints(wxDefaultSize, wxDefaultSize);
	m_mgr.SetManagedWindow(this);
	m_mgr.SetFlags(wxAUI_MGR_DEFAULT);

	m_mgr.AddPane(CreateNotebookDrawing(), wxAuiPaneInfo().Center().CaptionVisible(false).Dock().Resizable().FloatingSize(wxDefaultSize));
    m_mgr.AddPane(CreateToolbarDraft(), wxAuiPaneInfo().Name(_T("aui_draft")).ToolbarPane().Caption(_("drawing")).Layer(10).Top().Gripper());

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


wxAuiToolBar* MainFrame::CreateToolbarDraft(void)
{
    tool_draft = new wxAuiToolBar(this, ID_TOOL_DRAFT, wxDefaultPosition, wxDefaultSize, wxAUI_TB_DEFAULT_STYLE);
    tool_draft->AddTool(ID_BTN_DRAW_POINT, _("point"), wxBitmap(wxImage(_T("res\\icons\\icon_point.ico"))),
                        wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxEmptyString, NULL);
    tool_draft->AddTool(ID_BTN_DRAW_LINE, _("line"), wxBitmap(wxImage(_T("res\\icons\\icon_line.ico"))),
                        wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxEmptyString, NULL);
    tool_draft->AddTool(ID_BTN_DRAW_CIRCLE, _("circle"), wxBitmap(wxImage(_T("res\\icons\\icon_circle.ico"))),
                        wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxEmptyString, NULL);
    tool_draft->AddTool(ID_BTN_DRAW_SQUARE, _("square"), wxBitmap(wxImage(_T("res\\icons\\icon_square.ico"))),
                        wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxEmptyString, NULL);
    tool_draft->Realize();
    return tool_draft;
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

    if(button_id==ID_BTN_DRAW_POINT)
        cmd = "point";
    if(button_id==ID_BTN_DRAW_LINE)
        cmd = "line";
    if(button_id==ID_BTN_DRAW_CIRCLE)
        cmd = "circle";
    if(button_id==ID_BTN_DRAW_SQUARE)
        cmd = "square";

    m_interpreter.ExecuteCommand(cmd.ToStdString());
}
