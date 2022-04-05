#include "main_frame.h"
#include "classes/include/wxoccpanel.h"
#include <wx/artprov.h>


wxBEGIN_EVENT_TABLE(MainFrame, wxFrame)
    EVT_PAINT(MainFrame::OnPaint)
wxEND_EVENT_TABLE()


MainFrame::MainFrame(wxWindow* parent, wxWindowID id, const wxString& title,
          const wxPoint& pos, const wxSize& size, long style)
          :wxFrame(parent, id, title, pos, size, style)
{
    this->SetSizeHints(wxDefaultSize, wxDefaultSize);


	m_mgr.SetManagedWindow(this);
	m_mgr.SetFlags(wxAUI_MGR_DEFAULT);

	m_main_toolbar = new wxAuiToolBar(this,
                        wxID_ANY, wxDefaultPosition,
                        wxDefaultSize, wxAUI_TB_HORZ_LAYOUT);

	m_tool1 = m_main_toolbar->AddTool(wxID_ANY, wxT("tool1"),
                            wxArtProvider::GetBitmap(wxART_FILE_SAVE),
                            wxNullBitmap, wxITEM_NORMAL,
                            wxEmptyString, wxEmptyString, NULL);

	m_tool2 = m_main_toolbar->AddTool(wxID_ANY, wxT("tool2"),
                            wxArtProvider::GetBitmap(wxART_FILE_SAVE),
                            wxNullBitmap, wxITEM_NORMAL, wxEmptyString,
                            wxEmptyString, NULL);

	m_tool3 = m_main_toolbar->AddTool(wxID_ANY, wxT("tool3"),
                            wxArtProvider::GetBitmap(wxART_FILE_SAVE),
                            wxNullBitmap, wxITEM_NORMAL, wxEmptyString,
                            wxEmptyString, NULL );


	m_mgr.AddPane(m_main_toolbar, wxAuiPaneInfo().Name(_("main toolbar"))
               .ToolbarPane().Caption(_("menu")).Top().Gripper());

	m_auinotebook2 = new wxAuiNotebook(this, wxID_ANY, wxDefaultPosition,
                                    wxDefaultSize, wxAUI_NB_DEFAULT_STYLE);

	m_mgr.AddPane(m_auinotebook2, wxAuiPaneInfo().Left().PinButton(true)
               .Dock().Center().CaptionVisible(false).Resizable().FloatingSize(wxDefaultSize));

	draw_panel = new wxOccPanel(m_auinotebook2, wxID_ANY, wxDefaultPosition,
                        /*wxDefaultSize*/ wxSize(800,600), wxTAB_TRAVERSAL);

	m_auinotebook2->AddPage(draw_panel, wxT("a page"), false, wxNullBitmap);

	m_main_toolbar->Realize();

	m_mgr.Update();
	/**/
	this->Centre(wxBOTH);

	//Draw();
}

MainFrame::~MainFrame()
{
    m_mgr.UnInit();
}
