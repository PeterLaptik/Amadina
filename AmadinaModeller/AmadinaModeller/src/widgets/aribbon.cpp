#include "widgets/aribbon.h"
#include <wx/ribbon/buttonbar.h>

const int ARibbon::kPageMain = wxNewId();
const int ARibbon::kPageModelling = wxNewId();

const int ARibbon::kPanelFile = wxNewId();
const int ARibbon::kPanelView = wxNewId();
const int ARibbon::kPanelSketch = wxNewId();

ARibbon::ARibbon(wxWindow *parent, wxWindowID id)
    : wxRibbonBar(parent, id, wxDefaultPosition, wxDefaultSize, wxRIBBON_BAR_DEFAULT_STYLE)
{
    m_pages_by_id.insert(std::make_pair(kPageMain, new wxRibbonPage(this, kPageMain, _("Main"))));
    m_pages_by_id.insert(std::make_pair(kPageModelling, new wxRibbonPage(this, kPageModelling, _("Drawing"))));

    InitPanels();
}

ARibbon::~ARibbon()
{
    for (auto ptr : m_commands)
        delete ptr.second;
}

void ARibbon::InitPanels()
{
    CreatePanel(ARibbon::kPageMain, kPanelFile, _("File"));
    CreatePanel(ARibbon::kPageMain, kPanelView, _("View"));
    CreatePanel(ARibbon::kPageMain, kPanelSketch, _("Sketch"));
}

int ARibbon::CreatePanel(int page_id, int panel_id, const wxString &panel_name)
{
    auto it = m_pages_by_id.find(page_id);
    if (it == m_pages_by_id.end())
        return -1; // No page to append

    wxRibbonPage *parent = it->second;
    wxRibbonPanel *panel = new wxRibbonPanel(parent, panel_id, panel_name, wxNullBitmap,
        wxDefaultPosition, wxDefaultSize,
        wxRIBBON_PANEL_DEFAULT_STYLE | wxRIBBON_PANEL_NO_AUTO_MINIMISE);
    m_panels_by_id.insert(std::make_pair(panel_id, panel));

    return 0;
}

int ARibbon::AddButtonBar(int panel_id)
{
    auto it = m_panels_by_id.find(panel_id);
    if (it == m_panels_by_id.end())
        return -1;

    wxRibbonPanel *panel = it->second;
    int bar_id = wxNewId();

    wxRibbonButtonBar *bar = new wxRibbonButtonBar(panel, bar_id, wxDefaultPosition, wxDefaultSize, 0);
    m_button_bars_by_id.insert(std::make_pair(bar_id, bar));
    return bar_id;
}

void ARibbon::AddCommandButton(int bar_id, AbstractCommand *cmd, wxBitmap icon,
    const wxString &label, const wxString &help)
{
    if (!cmd)
        return;
    
    auto it = m_button_bars_by_id.find(bar_id);
    if (it == m_button_bars_by_id.end())
    {
        delete cmd;
        return; // No bar to add
    }

    wxRibbonButtonBar *bar = it->second;
    int button_id = wxNewId();
    bar->AddButton(button_id, label, icon, help);
    m_commands.insert(std::make_pair(button_id, cmd));
}
