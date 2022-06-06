#include "main_frame.h"
#include "resources/art.h"
#include "classes/include/wxoccpanel.h"
#include <wx/artprov.h>
#include <wx/ribbon/art.h>
#include <wx/ribbon/bar.h>
#include <wx/ribbon/buttonbar.h>

using modeller::art::Icons;
using modeller::art::get_icon;

wxBEGIN_EVENT_TABLE(MainFrame, wxFrame)
    EVT_PAINT(MainFrame::OnPaint)
wxEND_EVENT_TABLE()


MainFrame::MainFrame(wxWindow* parent, wxWindowID id, const wxString& title,
          const wxPoint& pos, const wxSize& size, long style)
          : wxFrame(parent, id, title, pos, size, style)
{
    this->SetSizeHints(wxDefaultSize, wxDefaultSize);
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

	m_notebook->AddPage(new wxOccPanel(this), "test");
}



MainFrame::~MainFrame()
{
    m_mgr.UnInit();
}

void MainFrame::RibbonInit()
{
    wxRibbonPage *m_ribbonPage6 = new wxRibbonPage(m_ribbon, wxID_ANY, wxT("Main"), wxArtProvider::GetBitmap(wxART_FILE_OPEN), 0);
    new wxRibbonPage(m_ribbon, wxID_ANY, wxT("Drawing"), wxArtProvider::GetBitmap(wxART_FILE_OPEN) , 0);
    wxRibbonPanel *m_ribbonPanel5 = new wxRibbonPanel(m_ribbonPage6, wxID_ANY, wxT("File") , wxNullBitmap ,
                                                      wxDefaultPosition, wxDefaultSize,
                                                      wxRIBBON_PANEL_DEFAULT_STYLE | wxRIBBON_PANEL_NO_AUTO_MINIMISE);
    wxRibbonPanel *m_ribbonPanel6 = new wxRibbonPanel(m_ribbonPage6, wxID_ANY, wxT("View") , wxNullBitmap ,
                                                      wxDefaultPosition, wxDefaultSize, wxRIBBON_PANEL_DEFAULT_STYLE);
    wxRibbonButtonBar *m_ribbonButtonBar5 = new wxRibbonButtonBar( m_ribbonPanel5,
                                                                  wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );

    wxRibbonButtonBar *m_ribbonButtonBar6 = new wxRibbonButtonBar( m_ribbonPanel6,
                                                                  wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );

    m_ribbonButtonBar5->AddDropdownButton( wxID_ANY, wxT("New"), wxArtProvider::GetBitmap(wxART_NEW), wxEmptyString);
    m_ribbonButtonBar5->AddButton(wxID_ANY, wxT("Open"), wxArtProvider::GetBitmap(wxART_FILE_OPEN), wxEmptyString);
    m_ribbonButtonBar5->AddButton(wxID_ANY, wxT("Save"), wxArtProvider::GetBitmap(wxART_FILE_SAVE), wxEmptyString);
    m_ribbonButtonBar5->AddButton(wxID_ANY, wxT("Save As"), wxArtProvider::GetBitmap(wxART_FILE_SAVE_AS), wxEmptyString);

    m_ribbonButtonBar6->AddButton(wxID_ANY, wxT("Top"), get_icon(Icons::ICO_VIEW_LEFT), wxEmptyString);
    m_ribbonButtonBar6->AddButton(wxID_ANY, wxT("Left"), get_icon(Icons::ICO_VIEW_LEFT), wxEmptyString);
    m_ribbonButtonBar6->AddButton(wxID_ANY, wxT("Front"), get_icon(Icons::ICO_VIEW_FRONT), wxEmptyString);
    m_ribbonButtonBar6->AddButton(wxID_ANY, wxT("Bottom"), get_icon(Icons::ICO_VIEW_BOTTOM), wxEmptyString);
    m_ribbonButtonBar6->AddButton(wxID_ANY, wxT("Right"), get_icon(Icons::ICO_VIEW_RIGHT), wxEmptyString);
    m_ribbonButtonBar6->AddButton(wxID_ANY, wxT("Back"), get_icon(Icons::ICO_VIEW_BACK), wxEmptyString);
}
