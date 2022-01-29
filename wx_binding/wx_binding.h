#ifndef WX_BINDING_H_INCLUDED
#define WX_BINDING_H_INCLUDED

// Binds kernel to GUI-interface
// Creates tool-bars, menus, etc.
// Created for

class wxFrame;
class wxAuiManager;
class wxAuiNotebook;
class CallableFrame;
class ViewPanel;
class CommandDispatcher;

namespace ui
{
    class UiMenuCommands;
}

#ifdef _MSC_VER
    #ifdef BUILD_DLL
        #define DLL_EXPORT __declspec(dllexport)
    #else
        #define DLL_EXPORT __declspec(dllimport)
    #endif
#else
    #define DLL_EXPORT
#endif

// Entry point
// GUI-dependent initializations
// Creates tool-bars/menus/buttons
// and initializes kernel commands
void DLL_EXPORT init_commands(wxFrame *parent,
                       wxAuiManager *mgr,
                       CommandDispatcher *dispatcher,
                       ui::UiMenuCommands *commands);


// Returns new instance of screen (panel)
DLL_EXPORT ViewPanel* create_screen(wxAuiNotebook *parent, CallableFrame *callable);

#endif // WX_BINDING_H_INCLUDED
