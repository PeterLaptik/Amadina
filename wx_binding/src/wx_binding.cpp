#include "../wx_binding.h"
#include <wx/frame.h>
#include <wx/aui/aui.h>
#include <wx/artprov.h>
// Kernel dependensies
#include "api/acommand.h"
#include "command/dispatcher.h"
#include "command/uicommands.h"


// Generates new toolbar
wxAuiToolBar* create_tool_bar(wxFrame *parent);

// Add filled tool-bar to AUI-manager
void add_toolbar_to_aui_manager(wxAuiToolBar *toolbar,
                                wxString caption,
                                wxString unique_name,
                                wxAuiManager *mgr);

// Adds tool to an existing toolbar
long add_tool(wxString name, wxString tooltip,
              wxBitmap *bitmap, wxAuiToolBar *toolbar);

// Appending and registration commands
void append_drawing_commands(wxAuiToolBar *toolbar,
                             CommandDispatcher *dispatcher,
                             ui::UiMenuCommands *commands);


//////////////////////////////////
//////                      //////
//////     Entry point      //////
//////    GUI-dependent     //////
//////                      //////
//////////////////////////////////
void init_commands(wxFrame *parent,
                    wxAuiManager *mgr,
                    CommandDispatcher *dispatcher,
                    ui::UiMenuCommands *commands)
{
    register_kernel_commands(dispatcher);
    wxAuiToolBar *drafting_bar = create_tool_bar(parent);
    append_drawing_commands(drafting_bar, dispatcher, commands);
    add_toolbar_to_aui_manager(drafting_bar, "drawing", "drafting_toolbar", mgr);
}

void append_drawing_commands(wxAuiToolBar *toolbar,
                             CommandDispatcher *dispatcher,
                             ui::UiMenuCommands *commands)
{
    wxBitmap img_pt(wxImage(_T("res\\icons\\icon_point.ico")));
    // Draw point
    // Button
    long id = add_tool("point", "Point", &img_pt, toolbar);
    dispatcher->RegisterHandler(id, "point");
     // Menu
    id = commands->AppendMenuCommand("Point", "point", ui::CMD_DRAW);
    dispatcher->RegisterHandler(id, "point");

    // Draw line

    wxBitmap img_line(wxImage(_T("res\\icons\\icon_line.ico")));
    id = add_tool("line", "Line", &img_line, toolbar);
    dispatcher->RegisterHandler(id, "line");
     // Menu
    id = commands->AppendMenuCommand("Line", "line", ui::CMD_DRAW);
    dispatcher->RegisterHandler(id, "line");

    // Draw line
    wxBitmap img_circle(wxImage(_T("res\\icons\\icon_circle.ico")));
    id = add_tool("circle", "Circle", &img_circle, toolbar);
    dispatcher->RegisterHandler(id, "circle");
     // Menu
    id = commands->AppendMenuCommand("Line", "line", ui::CMD_DRAW);
    dispatcher->RegisterHandler(id, "line");


    id = add_tool("delete", "Delete", &img_circle, toolbar);
    dispatcher->RegisterHandler(id, "delete");
}


long add_tool(wxString name, wxString tooltip,
              wxBitmap *bitmap, wxAuiToolBar *toolbar)
{
    long id = wxNewId();
    wxAuiToolBarItem *item = toolbar->AddTool(id, name, *bitmap,
                    *bitmap, wxITEM_NORMAL,
                    tooltip, wxEmptyString, NULL);
    return id;
}


wxAuiToolBar* create_tool_bar(wxFrame *parent)
{
    wxAuiToolBar *toolbar =  new wxAuiToolBar(parent,
                                              wxNewId(),
                                              wxDefaultPosition,
                                              wxDefaultSize,
                                              wxAUI_TB_DEFAULT_STYLE);
    return toolbar;
}

void add_toolbar_to_aui_manager(wxAuiToolBar *toolbar,
                                wxString caption,
                                wxString unique_name,
                                wxAuiManager *mgr)
{
    mgr->AddPane(toolbar, wxAuiPaneInfo()
                 .Name(unique_name)
                 .ToolbarPane()
                 .Caption(caption)
                 .Layer(10)
                 .Top().Gripper());
}
