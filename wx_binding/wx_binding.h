#ifndef WX_BINDING_H_INCLUDED
#define WX_BINDING_H_INCLUDED

class wxFrame;
class wxAuiManager;

class CommandDispatcher;

namespace ui
{
    class UiMenuCommands;
}


// Entry point
// GUI-dependent initializations
// Allows to add tool-bars/menus/buttons
void init_commands(wxFrame *parent,
                       wxAuiManager *mgr,
                       CommandDispatcher *dispatcher,
                       ui::UiMenuCommands *commands);


#endif // WX_BINDING_H_INCLUDED
