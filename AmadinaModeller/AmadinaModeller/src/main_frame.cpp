#include "main_frame.h"
#include "abstract_modeller.h"
#include "factory.h"
#include "../resources/art.h"
//#include "commands_names.h"
//#include "wxpointinput.h"
//#include "wxoccpanel.h"
#include <wx/msgdlg.h>
#include <wx/artprov.h>
#include <wx/treectrl.h>
#include <wx/ribbon/art.h>
#include <wx/ribbon/bar.h>
#include <wx/ribbon/buttonbar.h>

//using namespace cad::modeller::command::names;
using modeller::art::Icon;
using modeller::art::get_icon;

wxBEGIN_EVENT_TABLE(MainFrame, wxFrame)
    EVT_PAINT(MainFrame::OnPaint)
    EVT_RIBBONBUTTONBAR_CLICKED(wxID_ANY, MainFrame::OnButtonClicked)
    //EVT_RIBBONBAR_TAB_LEFT_DCLICK(wxID_ANY, MainFrame::OnButtonClicked)
wxEND_EVENT_TABLE()


MainFrame::MainFrame(wxWindow* parent, wxWindowID id, const wxString& title,
          const wxPoint& pos, const wxSize& size, long style)
          : wxFrame(parent, id, title, pos, size, style)
{
    this->SetSizeHints(1300, 850);
    this->SetPosition(wxPoint(0,0));
    m_mgr.SetManagedWindow(this);
	m_mgr.SetFlags(wxAUI_MGR_DEFAULT);

    m_main_panel = new wxPanel(this, wxID_ANY, wxDefaultPosition,
                               wxDefaultSize, wxTAB_TRAVERSAL);

	m_mgr.AddPane(m_main_panel, wxAuiPaneInfo().Left()
               .CaptionVisible(false)
               .CloseButton(false)
               .PinButton(true)
               .Dock()
               .Resizable()
               .FloatingSize(wxDefaultSize)
               .CentrePane());

    m_main_sizer = new wxBoxSizer(wxVERTICAL);
    m_ribbon = new wxRibbonBar(m_main_panel, wxID_ANY, wxDefaultPosition,
                               wxDefaultSize, wxRIBBON_BAR_DEFAULT_STYLE);

    m_ribbon->SetArtProvider(new wxRibbonAUIArtProvider);

    RibbonInit();

    m_ribbon->Realise();
    m_main_sizer->Add(m_ribbon, 0, wxEXPAND | wxALL, 0);

    m_notebook = new wxAuiNotebook(m_main_panel, wxID_ANY, wxDefaultPosition,
                                   wxDefaultSize, wxAUI_NB_DEFAULT_STYLE);
	m_main_sizer->Add(m_notebook, 1, wxEXPAND | wxALL, 0);

    m_main_panel->SetSizer(m_main_sizer);
	m_main_panel->Layout();
	m_main_sizer->Fit(m_main_panel);

	m_status_bar = this->CreateStatusBar(1, wxSTB_SIZEGRIP, wxID_ANY);
	m_mgr.Update();
	this->Centre(wxBOTH);

	m_modeller = get_abstract_modeller(this);//new wxModeller3D(this);
	m_notebook->AddPage(m_modeller, "test");
}



MainFrame::~MainFrame()
{
    m_mgr.UnInit();
}

void MainFrame::RibbonInit()
{
    wxRibbonPage *m_ribbonPage6 = new wxRibbonPage(m_ribbon, wxID_ANY, wxT("Main"), wxArtProvider::GetBitmap(wxART_FILE_OPEN), 0);
    wxRibbonPage *m_ribbon_drawing = new wxRibbonPage(m_ribbon, wxID_ANY, wxT("Drawing"), wxArtProvider::GetBitmap(wxART_FILE_OPEN) , 0);
    wxRibbonPanel *m_ribbonPanel5 = new wxRibbonPanel(m_ribbonPage6, wxID_ANY, wxT("File") , wxNullBitmap ,
                                                      wxDefaultPosition, wxDefaultSize,
                                                      wxRIBBON_PANEL_DEFAULT_STYLE | wxRIBBON_PANEL_NO_AUTO_MINIMISE);
    wxRibbonPanel *m_ribbonPanel6 = new wxRibbonPanel(m_ribbonPage6, wxID_ANY, wxT("View") , wxNullBitmap ,
                                                      wxDefaultPosition, wxDefaultSize, wxRIBBON_PANEL_DEFAULT_STYLE);
    wxRibbonButtonBar *m_ribbonButtonBar5 = new wxRibbonButtonBar( m_ribbonPanel5,
                                                                  wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );

    m_ribbonButtonBar6 = new wxRibbonButtonBar( m_ribbonPanel6,
                                                                  wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );

    m_ribbonButtonBar5->AddDropdownButton( wxID_ANY, wxT("New"), wxArtProvider::GetBitmap(wxART_NEW), wxEmptyString);
    m_ribbonButtonBar5->AddButton(wxID_ANY, wxT("Open"), wxArtProvider::GetBitmap(wxART_FILE_OPEN), wxEmptyString);
    m_ribbonButtonBar5->AddButton(wxID_ANY, wxT("Save"), wxArtProvider::GetBitmap(wxART_FILE_SAVE), wxEmptyString);
    m_ribbonButtonBar5->AddButton(wxID_ANY, wxT("Save As"), wxArtProvider::GetBitmap(wxART_FILE_SAVE_AS), wxEmptyString);

    //AddButtonCommand(m_ribbonButtonBar6, wxT("Top"), get_icon(Icon::ICO_VIEW_TOP), wxEmptyString, CMD_VIEW_TOP);
    //AddButtonCommand(m_ribbonButtonBar6, wxT("Left"), get_icon(Icon::ICO_VIEW_LEFT), wxEmptyString, CMD_VIEW_LEFT);
    //AddButtonCommand(m_ribbonButtonBar6, wxT("Front"), get_icon(Icon::ICO_VIEW_FRONT), wxEmptyString, CMD_VIEW_FRONT);
    //AddButtonCommand(m_ribbonButtonBar6, wxT("Bottom"), get_icon(Icon::ICO_VIEW_BOTTOM), wxEmptyString, CMD_VIEW_BOTTOM);
    //AddButtonCommand(m_ribbonButtonBar6, wxT("Right"), get_icon(Icon::ICO_VIEW_RIGHT), wxEmptyString, CMD_VIEW_RIGHT);
    //AddButtonCommand(m_ribbonButtonBar6, wxT("Back"), get_icon(Icon::ICO_VIEW_BACK), wxEmptyString, CMD_VIEW_BACK);

    AddSystemCommand(m_ribbonButtonBar6, wxT("Sketch"), get_icon(Icon::ICO_SKETCH_MODE),
                     wxEmptyString, true, &MainFrame::SketchModeHandler);

    m_ribbonButtonBar6->AddButton(wxID_ANY, wxT("Point"), get_icon(Icon::ICO_EMPTY), wxEmptyString);
    m_ribbonButtonBar6->AddButton(wxID_ANY, wxT("Line"), get_icon(Icon::ICO_SKETCH_LINE), wxEmptyString);
}

void MainFrame::AddButtonCommand(wxRibbonButtonBar *bar, const wxString &label,
                              const wxBitmap &bitmap, const wxString &help,
                              const std::string &command_name)
{
    wxWindowID button_id = wxNewId();
    bar->AddButton(button_id, label, bitmap, wxEmptyString);
    m_commands_buttons_map.insert(std::pair<wxWindowID, std::string>(button_id, command_name));
}



void MainFrame::AddSystemCommand(wxRibbonButtonBar *bar, const wxString &label,
                              const wxBitmap &bitmap, const wxString &help,
                              bool is_toggle, CommandHandler handler)
{
    wxWindowID button_id = wxNewId();
    is_toggle ? bar->AddToggleButton(button_id, label, bitmap, wxEmptyString)
                : bar->AddButton(button_id, label, bitmap, wxEmptyString);
    m_system_commands_map.insert(std::pair<wxWindowID,CommandHandler>(button_id, handler));
}

void MainFrame::OnButtonClicked(wxRibbonButtonBarEvent &event)
{
    m_modeller->Test();
    //wxWindowID id = event.GetId();
    //// Check for a system command
    //auto it_sys = m_system_commands_map.find(id);
    //if(it_sys!=m_system_commands_map.end())
    //{
    //    CommandHandler meth = it_sys->second;
    //    (this->*meth)(event);
    //    return;
    //}
    //// Check for a regular command
    //// Find command name
    //auto it = m_commands_buttons_map.find(id);
    //if(it==m_commands_buttons_map.end())
    //    return;
    //// Try to run command in the context
    //Context *ctx = m_modeller->GetContext();
    //ctx->RunCommand(it->second);
}

void MainFrame::SketchModeHandler(wxEvent &event)
{
    //Context *ctx = m_modeller->GetContext();
    //wxRibbonButtonBarEvent &evt = dynamic_cast<wxRibbonButtonBarEvent&>(event);
    //bool is_pushed = evt.IsChecked();

    //Handle(AIS_ViewCube) view_cube = ctx->GetViewCube();
    //Handle(AIS_ViewCubeOwner) click_emulator(new AIS_ViewCubeOwner(view_cube, V3d_Zpos));
    //view_cube->HandleClick(click_emulator);

    //ctx->SetScreenMode(is_pushed ? ScreenMode::SCREEN_SKETCHING : ScreenMode::SCREEN_MODELLING);
    //m_modeller->Test();
    //wxMessageBox("OK");
}
