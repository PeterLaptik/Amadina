#ifndef MAIN_FRAME_H_INCLUDED
#define MAIN_FRAME_H_INCLUDED

#include <wx/aui/aui.h>


const wxSize DEFAULT_WINDOW_SIZE = wxSize(800,600);

class wxRibbonBar;
class wxRibbonButtonBarEvent;
class wxModeller3D;

class MainFrame: public wxFrame
{
    public:
        MainFrame(wxWindow* parent,
                  wxWindowID id = wxID_ANY,
                  const wxString& title = wxEmptyString,
                  const wxPoint& pos = wxDefaultPosition,
                  const wxSize& size = DEFAULT_WINDOW_SIZE,
                  long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL);

        ~MainFrame();

    protected:
        void OnButtonClicked(wxRibbonButtonBarEvent &event);
		wxAuiManager m_mgr;

		// All widgets (including a ribbon bar) are situated
		// on the following panel
		wxPanel *m_main_panel;

		// Main sizer: vertical
		wxBoxSizer* m_main_sizer;

		wxRibbonBar *m_ribbon;
		wxAuiNotebook *m_notebook;
		wxStatusBar *m_status_bar;
		wxModeller3D *m_modeller;

    private:
        void RibbonInit(void);

    DECLARE_EVENT_TABLE()
};

#endif // MAIN_FRAME_H_INCLUDED
