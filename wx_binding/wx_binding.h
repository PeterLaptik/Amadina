#ifndef WX_BINDING_H_INCLUDED
#define WX_BINDING_H_INCLUDED

class wxFrame;
class wxAuiManager;
class wxAuiNotebook;
class ViewPanel;
class CommandDispatcher;

namespace ui
{
    class UiMenuCommands;
}

#ifdef BUILD_DLL
    #define DLL_EXPORT __declspec(dllexport)
#else
    #define DLL_EXPORT __declspec(dllimport)
#endif

// Entry point
// GUI-dependent initializations
// Creates tool-bars/menus/buttons
// and initialize kernel commands
void DLL_EXPORT init_commands(wxFrame *parent,
                       wxAuiManager *mgr,
                       CommandDispatcher *dispatcher,
                       ui::UiMenuCommands *commands);


DLL_EXPORT ViewPanel* create_screen(wxAuiNotebook *parent, ViewPanel* panel);

#endif // WX_BINDING_H_INCLUDED
