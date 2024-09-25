/***************************************************************
 * Name:      wxTestMain.cpp
 * Purpose:   Code for Application Frame
 * Author:     ()
 * Created:   2022-07-26
 * Copyright:  ()
 * License:
 **************************************************************/

#include "wxTestMain.h"
#include "command_panel.h"
#include <wx/msgdlg.h>

//(*InternalHeaders(wxTestFrame)
#include <wx/intl.h>
#include <wx/string.h>
//*)

//helper functions
enum wxbuildinfoformat {
    short_f, long_f };

wxString wxbuildinfo(wxbuildinfoformat format)
{
    wxString wxbuild(wxVERSION_STRING);

    if (format == long_f )
    {
#if defined(__WXMSW__)
        wxbuild << _T("-Windows");
#elif defined(__UNIX__)
        wxbuild << _T("-Linux");
#endif

#if wxUSE_UNICODE
        wxbuild << _T("-Unicode build");
#else
        wxbuild << _T("-ANSI build");
#endif // wxUSE_UNICODE
    }

    return wxbuild;
}

std::vector<std::string> auto_ist = {"abc", "abx", "aby", "ert", "erz", "ert", "erz", "ert", "erz", "ert", "erz", "ert", "erz", "ert", "erz", 
    "LINE", "CIRCLE", "ARC", "CUBE"};

//(*IdInit(wxTestFrame)
const long wxTestFrame::ID_BUTTON1 = wxNewId();
const long wxTestFrame::ID_PANEL2 = wxNewId();
const long wxTestFrame::ID_PANEL1 = wxNewId();
const long wxTestFrame::idMenuQuit = wxNewId();
const long wxTestFrame::idMenuAbout = wxNewId();
const long wxTestFrame::ID_STATUSBAR1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(wxTestFrame,wxFrame)
    //(*EventTable(wxTestFrame)
    //*)
END_EVENT_TABLE()

wxTestFrame::wxTestFrame(wxWindow* parent,wxWindowID id)
{
    ////(*Initialize(wxTestFrame)
      wxBoxSizer* BoxSizer1;
      wxBoxSizer* BoxSizer0;
      wxMenu* Menu1;
      wxMenu* Menu2;
      wxMenuBar* MenuBar1;
      wxMenuItem* MenuItem1;
      wxMenuItem* MenuItem2;
      CommandPanel *m_cmd;

      BoxSizer0 = new wxBoxSizer(wxVERTICAL);
      BoxSizer1 = new wxBoxSizer(wxVERTICAL);

      Create(parent, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("wxID_ANY"));
      SetClientSize(wxSize(870,474));
      AuiManager1 = new wxAuiManager(this, wxAUI_MGR_DEFAULT);
      Panel1 = new wxPanel(this, ID_PANEL1);
      
      Panel1->SetSizer(BoxSizer1);
      
      Panel2 = new wxPanel(Panel1, ID_PANEL2, wxDefaultPosition, wxDefaultSize, wxSIMPLE_BORDER | wxTAB_TRAVERSAL, _T("ID_PANEL2"));
      BoxSizer1->Add(Panel2, 1, wxALL | wxEXPAND, 5);
      
      m_cmd = new CommandPanel(Panel1);
      BoxSizer1->Add(m_cmd, 1, wxALL | wxEXPAND, 5);

      SetSizer(BoxSizer0);
      Layout();

      AuiManager1->AddPane(Panel1, wxAuiPaneInfo().Name(_T("PaneName")).DefaultPane().Caption(_("Pane test")).CaptionVisible().Center().BestSize(wxSize(840,422)));
      AuiManager1->Update();
      MenuBar1 = new wxMenuBar();
      Menu1 = new wxMenu();
      MenuItem1 = new wxMenuItem(Menu1, idMenuQuit, _("Quit\tAlt-F4"), _("Quit the application"), wxITEM_NORMAL);
      Menu1->Append(MenuItem1);
      MenuBar1->Append(Menu1, _("&File"));
      Menu2 = new wxMenu();
      MenuItem2 = new wxMenuItem(Menu2, idMenuAbout, _("About\tF1"), _("Show info about this application"), wxITEM_NORMAL);
      Menu2->Append(MenuItem2);
      MenuBar1->Append(Menu2, _("Help"));
      SetMenuBar(MenuBar1);

      Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&wxTestFrame::OnButton1Click);
      Connect(idMenuQuit,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&wxTestFrame::OnQuit);
      Connect(idMenuAbout,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&wxTestFrame::OnAbout);
      //*)
}

wxTestFrame::~wxTestFrame()
{
    //(*Destroy(wxTestFrame)
    //*)
    AuiManager1->UnInit();
    delete AuiManager1;
}

void wxTestFrame::OnQuit(wxCommandEvent& event)
{
    Close();
}

void wxTestFrame::OnAbout(wxCommandEvent& event)
{
    wxString msg = wxbuildinfo(long_f);
    wxMessageBox(msg, _("Welcome to..."));
}

void wxTestFrame::OnButton1Click(wxCommandEvent& event)
{
    //$(#msvc.base)\$(#msvc.version)\bin\Hostx64\$(#msvc.platform)\dial->Show();
}


