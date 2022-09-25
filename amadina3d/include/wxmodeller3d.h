#ifndef WXMODELLER3D_H
#define WXMODELLER3D_H

#include <wx/panel.h>

class wxTreeCtrl;
class wxOccPanel;
class wxBoxSizer;
class wxSplitterWindow;

///\brief Composite widget for interactive modelling
class wxModeller3D: public wxPanel
{
    public:
        wxModeller3D(wxWindow *parent,
                    wxWindowID winid = wxID_ANY,
                    const wxPoint &pos = wxDefaultPosition,
                    const wxSize &size = wxDefaultSize,
                    long style = wxTAB_TRAVERSAL | wxNO_BORDER,
                    const wxString &name = wxPanelNameStr);

        virtual ~wxModeller3D();

        void Test(void);

    private:
        wxTreeCtrl *m_model_tree;
        wxOccPanel *m_occpanel;
        wxBoxSizer *m_sizer;
        wxSplitterWindow *m_splitter;

};

#endif // WXMODELLER3D_H
