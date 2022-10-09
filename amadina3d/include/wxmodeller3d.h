#ifndef WXMODELLER3D_H
#define WXMODELLER3D_H

#include "context.h"
#include <wx/panel.h>
#include <memory>

class wxTreeCtrl;
class wxOccPanel;
class wxBoxSizer;
class wxSplitterWindow;

using cad::modeller::Context;

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

        Context* GetContext(void) const;

        void Test(void);

    private:
        std::unique_ptr<Context> m_context;
        wxTreeCtrl *m_model_tree;
        wxOccPanel *m_occpanel;
        wxBoxSizer *m_sizer;
        wxSplitterWindow *m_splitter;

};

#endif // WXMODELLER3D_H
