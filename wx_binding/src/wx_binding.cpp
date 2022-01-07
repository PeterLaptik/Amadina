#include "../wx_binding.h"
#include "../res/provider.h"
#include <wx/frame.h>
#include <wx/aui/aui.h>
#include <wx/artprov.h>

// Kernel dependencies
#include "api/acommand.h"
#include "context/context.h"
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
              wxBitmap bitmap, wxAuiToolBar *toolbar);

// Appending and registration commands
void append_drawing_commands(wxAuiToolBar *toolbar,
                             CommandDispatcher *dispatcher,
                             ui::UiMenuCommands *commands);

void append_edit_commands(wxAuiToolBar *toolbar,
                             CommandDispatcher *dispatcher,
                             ui::UiMenuCommands *commands);



/////////////////////////////////////////////////////////
//////                                             //////
//////                  Entry point                //////
//////                 GUI-dependent               //////
//////                                             //////
/////////////////////////////////////////////////////////
void init_commands(wxFrame *parent,
                    wxAuiManager *mgr,
                    CommandDispatcher *dispatcher,
                    ui::UiMenuCommands *commands)
{
    register_kernel_commands(dispatcher);
    Context::AssignCommandDispatcher(dispatcher);
    // Drawing
    wxAuiToolBar *drafting_bar = create_tool_bar(parent);
    append_drawing_commands(drafting_bar, dispatcher, commands);
    add_toolbar_to_aui_manager(drafting_bar, "drawing", "drawing_toolbar", mgr);
    // Editing
    wxAuiToolBar *edit_bar = create_tool_bar(parent);
    append_edit_commands(edit_bar, dispatcher, commands);
    add_toolbar_to_aui_manager(edit_bar, "edit", "edit_toolbar", mgr);
}


void append_drawing_commands(wxAuiToolBar *toolbar,
                             CommandDispatcher *dispatcher,
                             ui::UiMenuCommands *commands)
{
    // Draw point
    long id = add_tool("point", "Point", get_icon(ICON_POINT), toolbar);
    dispatcher->RegisterHandler(id, "point");
    id = commands->AppendMenuCommand("Point", "point", ui::CMD_DRAW);
    dispatcher->RegisterHandler(id, "point");

    // Draw line
    id = add_tool("line", "Line", get_icon(ICON_LINE), toolbar);
    dispatcher->RegisterHandler(id, "line");
    id = commands->AppendMenuCommand("Line", "line", ui::CMD_DRAW);
    dispatcher->RegisterHandler(id, "line");

    // Draw circle
    id = add_tool("circle", "Circle", get_icon(ICON_CIRCLE), toolbar);
    dispatcher->RegisterHandler(id, "circle");
    id = commands->AppendMenuCommand("Circle", "circle", ui::CMD_DRAW);
    dispatcher->RegisterHandler(id, "circle");

    // Draw circle
    id = add_tool("arc", "Arc", get_icon(ICON_ARC_CENTER), toolbar);
    dispatcher->RegisterHandler(id, "arc");
    id = commands->AppendMenuCommand("Arc", "arc", ui::CMD_DRAW);
    dispatcher->RegisterHandler(id, "arc");
}


void append_edit_commands(wxAuiToolBar *toolbar,
                             CommandDispatcher *dispatcher,
                             ui::UiMenuCommands *commands)
{
    long id = add_tool("delete", "Delete", get_icon(ICON_DELETE), toolbar);
    dispatcher->RegisterHandler(id, "delete");
    id = commands->AppendMenuCommand("Delete", "delete", ui::CMD_DRAW);
    dispatcher->RegisterHandler(id, "delete");


    id = add_tool("copy", "Copy", get_icon(ICON_COPY), toolbar);
    dispatcher->RegisterHandler(id, "copy");
    id = commands->AppendMenuCommand("Copy", "copy", ui::CMD_DRAW);
    dispatcher->RegisterHandler(id, "copy");

    id = add_tool("cut", "Cut", get_icon(ICON_CUT), toolbar);
    id = add_tool("paste", "Paste", get_icon(ICON_PASTE), toolbar);
    dispatcher->RegisterHandler(id, "paste");
    id = commands->AppendMenuCommand("Paste", "paste", ui::CMD_DRAW);
    dispatcher->RegisterHandler(id, "paste");

    id = add_tool("move", "Move", get_icon(ICON_MOVE), toolbar);
}


// Adds tool to existing toolbar
long add_tool(wxString name, wxString tooltip,
              wxBitmap bitmap, wxAuiToolBar *toolbar)
{
    long id = wxNewId();
    wxAuiToolBarItem *item = toolbar->AddTool(id, name, bitmap,
                    bitmap, wxITEM_NORMAL,
                    tooltip, wxEmptyString, NULL);
    return id;
}

// Creates new toolbar
wxAuiToolBar* create_tool_bar(wxFrame *parent)
{
    wxAuiToolBar *toolbar =  new wxAuiToolBar(parent,
                                              wxNewId(),
                                              wxDefaultPosition,
                                              wxDefaultSize,
                                              wxAUI_TB_DEFAULT_STYLE);
    return toolbar;
}

// Adds a toolbar to aui manager
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
