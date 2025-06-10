#ifndef WXMODELLER3D_H
#define WXMODELLER3D_H

#include "abstract_modeller.h"
#include "wxoccpanel_styles.h"

class wxTreeCtrl;
class wxOccPanel;
class wxBoxSizer;
class wxSplitterWindow;
class wxModelTree;

namespace cad::app
{
    class ApplicationContext;
}

using cad::app::SheetContext;
using cad::app::ApplicationContext;

///\brief Composite widget for interactive modelling
class wxModeller3D:  public wxAbstractModeller
{
    public:
        wxModeller3D(wxWindow *parent, ApplicationContext *m_app_context);

        ~wxModeller3D() override;

        void RefreshView(void);

        SheetContext* GetContext();

        void Test(void) override;

    private:
        ApplicationContext *m_app_context;
        SheetContext *m_sheet_context;
        wxModelTree *m_model_tree;  // left-side panel, contains list of items and operations
        wxOccPanel *m_occpanel;     // canvas to draw
        wxBoxSizer *m_sizer;
        wxSplitterWindow *m_splitter;
        wxOcctStylesContainer m_styles_container;

};

#endif // WXMODELLER3D_H
