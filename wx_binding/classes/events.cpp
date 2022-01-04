#include "events.h"

MouseMoveEvent::MouseMoveEvent(wxEventType commandType)
    :  wxCommandEvent(commandType, 0)
{ }

MouseMoveEvent::MouseMoveEvent(const MouseMoveEvent &event)
    :  wxCommandEvent(event)
{
    x = event.x;
    y = event.y;
}

wxEvent* MouseMoveEvent::Clone() const
{
    return new MouseMoveEvent(*this);
}
