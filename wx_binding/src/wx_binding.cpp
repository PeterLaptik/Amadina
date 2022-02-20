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

// Appends command to toolbar and menu if necessary
void append_command(wxAuiToolBar* toolbar,
    CommandDispatcher* dispatcher,
    ui::UiMenuCommands* commands,
    const std::string& name,
    const std::string& desc,
    ICONS icon,
    ui::CommandType type = ui::CMD_NO_MENU);

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
    append_command(toolbar, dispatcher, commands, "point", "Point", ICON_POINT, ui::CMD_DRAW);
    append_command(toolbar, dispatcher, commands, "line", "Line", ICON_LINE, ui::CMD_DRAW);
    append_command(toolbar, dispatcher, commands, "circle", "Circle", ICON_CIRCLE, ui::CMD_DRAW);
    append_command(toolbar, dispatcher, commands, "circlep", "Circle", ICON_CIRCLE_POINTS, ui::CMD_DRAW);
    append_command(toolbar, dispatcher, commands, "arc", "Arc", ICON_ARC_CENTER, ui::CMD_DRAW);
    append_command(toolbar, dispatcher, commands, "arcp", "Arc", ICON_ARC_POINTS, ui::CMD_DRAW);
    append_command(toolbar, dispatcher, commands, "ellipse", "Ellipse", ICON_ELLIPCE, ui::CMD_DRAW);
}


void append_edit_commands(wxAuiToolBar *toolbar,
                             CommandDispatcher *dispatcher,
                             ui::UiMenuCommands *commands)
{
    append_command(toolbar, dispatcher, commands, "delete", "Delete", ICON_DELETE, ui::CMD_EDIT);
    append_command(toolbar, dispatcher, commands, "copy", "Copy", ICON_COPY, ui::CMD_EDIT);
    append_command(toolbar, dispatcher, commands, "cut", "Cut", ICON_CUT, ui::CMD_EDIT);
    append_command(toolbar, dispatcher, commands, "paste", "Paste", ICON_PASTE, ui::CMD_EDIT);
    append_command(toolbar, dispatcher, commands, "move", "Move", ICON_MOVE, ui::CMD_EDIT);
}

void append_command(wxAuiToolBar* toolbar,
                    CommandDispatcher* dispatcher,
                    ui::UiMenuCommands* commands,
                    const std::string &name,
                    const std::string &desc,
                    ICONS icon,
                    ui::CommandType type)
{
    long id = add_tool(name, desc, get_icon(icon), toolbar);
    dispatcher->RegisterHandler(id, name);
    if (type != ui::CMD_NO_MENU)
    {
        id = commands->AppendMenuCommand(desc, name, type);
        dispatcher->RegisterHandler(id, name);
    }
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
