#ifndef A_RIBBON_INCLUDED_H
#define A_RIBBON_INCLUDED_H

#include <wx/ribbon/bar.h>
#include <map>

class wxWindow;
class AbstractCommand;
class wxRibbonButtonBar;

class ARibbon: public wxRibbonBar
{
    public:
        ARibbon(wxWindow *parent, wxWindowID id = wxID_ANY);

        ~ARibbon() override;

        static const int kPanelFile;
        static const int kPanelView;
        static const int kPanelSketch;

        int AddButtonBar(int panel_id);

        void AddCommandButton(int bar_id, AbstractCommand *cmd, wxBitmap icon,
                        const wxString &label, const wxString &help);


    private:
        void InitPanels();
        int CreatePanel(int page_id, int panel_id, const wxString &panel_name);

        static const int kPageMain;
        static const int kPageModelling;

        // Mapping for pages, panels
        std::map<int, wxRibbonPage*> m_pages_by_id;
        std::map<int, wxRibbonPanel*> m_panels_by_id;
        std::map<int, wxRibbonButtonBar*> m_button_bars_by_id;

        // Commands
        std::map<int, AbstractCommand*> m_commands;
};

#endif