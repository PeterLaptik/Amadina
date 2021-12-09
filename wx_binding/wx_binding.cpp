#include "wx_binding.h"
#include "../kernel/command/dispatcher.h"
#include "../kernel/command/uicommands.h"
#include "../kernel/builders/point_cmd.h"
#include <wx/frame.h>
#include <wx/aui/aui.h>

// Generates new toolbar
wxAuiToolBar* add_tool_bar(wxString caption,
                           wxString unique_name,
                           wxFrame *parent,
                           wxAuiManager *mgr);
// Adds tool to an existing toolbar
long add_tool(wxString name, wxString tooltip,
              wxBitmap *bitmap, wxAuiToolBar *toolbar);
// Appending and registration commands
void append_drawing_commands(wxAuiToolBar *toolbar,
                             CommandDispatcher *dispatcher,
                             ui::UiMenuCommands *commands);

//
// Entry point
// GUI-dependent
//
void init_commands(wxFrame *parent,
                    wxAuiManager *mgr,
                    CommandDispatcher *dispatcher,
                    ui::UiMenuCommands *commands)
{
    wxAuiToolBar *drafting_bar = add_tool_bar("drawing", "drafting_toolbar", parent, mgr);
    append_drawing_commands(drafting_bar, dispatcher, commands);

}

void append_drawing_commands(wxAuiToolBar *toolbar,
                             CommandDispatcher *dispatcher,
                             ui::UiMenuCommands *commands)
{
    wxBitmap img(wxImage(_T("res\\icons\\icon_point.ico")));
    // Draw point
    // Button
    long id = add_tool("point", "Point", &img, toolbar);
    dispatcher->RegisterCommand(new CmdPoint(), "point");
    dispatcher->RegisterHandler(id, "point");
    // Menu
    id = commands->AppendMenuCommand("Point", "point", ui::CMD_DRAW);
    dispatcher->RegisterHandler(id, "point");
    toolbar->Realize();
}


long add_tool(wxString name, wxString tooltip,
              wxBitmap *bitmap, wxAuiToolBar *toolbar)
{
    long id = wxNewId();
    toolbar->AddTool(id, name, *bitmap,
                    wxNullBitmap, wxITEM_NORMAL,
                    tooltip, wxEmptyString, NULL);
    return id;
}


wxAuiToolBar* add_tool_bar(wxString caption,
                           wxString unique_name,
                           wxFrame *parent,
                           wxAuiManager *mgr)
{
    wxAuiToolBar *toolbar =  new wxAuiToolBar(parent,
                                              wxNewId(),
                                              wxDefaultPosition,
                                              wxDefaultSize,
                                              wxAUI_TB_DEFAULT_STYLE);
    mgr->AddPane(toolbar, wxAuiPaneInfo()
                 .Name(unique_name)
                 .ToolbarPane()
                 .Caption(caption)
                 .Layer(10)
                 .Top().Gripper());

    return toolbar;
}

