#ifndef WXMODELLER3D_H
#define WXMODELLER3D_H

#include "abstract_modeller.h"
#include "context.h"

class wxTreeCtrl;
class wxOccPanel;
class wxBoxSizer;
class wxSplitterWindow;
class wxCadHistoryTree;

using cad::modeller::Context;

///\brief Composite widget for interactive modelling
class wxModeller3D:  public wxAbstractModeller
{
    public:
        wxModeller3D(wxWindow *parent,
                    wxWindowID winid = wxID_ANY,
                    const wxPoint &pos = wxDefaultPosition,
                    const wxSize &size = wxDefaultSize,
                    long style = wxTAB_TRAVERSAL | wxNO_BORDER,
                    const wxString &name = wxPanelNameStr);

        ~wxModeller3D() override;

        void RefreshView(void);

        Context* GetContext(void) const;

        void Test(void) override;

    private:
        Context *m_context;
        wxCadHistoryTree *m_model_tree;
        wxOccPanel *m_occpanel;
        wxBoxSizer *m_sizer;
        wxSplitterWindow *m_splitter;

};

#endif // WXMODELLER3D_H
