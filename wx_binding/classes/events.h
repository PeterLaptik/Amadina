#ifndef EVENTS_H_INCLUDED
#define EVENTS_H_INCLUDED

#include <wx/event.h>

#ifdef _MSC_VER
    #ifdef BUILD_DLL
        #define DLL_EXPORT __declspec(dllexport)
    #else
        #define DLL_EXPORT __declspec(dllimport)
    #endif
#else
    #define DLL_EXPORT
#endif


class MouseMoveEvent;
wxDECLARE_EVENT(wxCAD_PANEL_MOVE, MouseMoveEvent);


class DLL_EXPORT MouseMoveEvent: public wxCommandEvent
{
    public:
        double x;
        double y;

    MouseMoveEvent(wxEventType commandType = wxCAD_PANEL_MOVE);

	MouseMoveEvent(const MouseMoveEvent &event);

	wxEvent* Clone() const;
};

#endif // EVENTS_H_INCLUDED
