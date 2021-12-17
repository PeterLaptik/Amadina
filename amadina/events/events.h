#ifndef EVENTS_H_INCLUDED
#define EVENTS_H_INCLUDED

#include <wx/event.h>

class wxEventConsoleInput;
wxDECLARE_EVENT(wxCONSOLE_INPUT, wxEventConsoleInput);

/**\brief Console input event.
* Occurs on input line 'enter'-key pressed.
*/
class wxEventConsoleInput: public wxCommandEvent
{
    public:
        wxEventConsoleInput(wxString input, wxEventType commandType = wxCONSOLE_INPUT, int id = 0)
                    :  wxCommandEvent(commandType, id), m_input(input)
        { }

        wxEventConsoleInput(const wxEventConsoleInput& event)
                    :  wxCommandEvent(event)
        {
            SetEventType(wxCONSOLE_INPUT);
            m_input = event.m_input;
        }

        wxEvent* Clone() const { return new wxEventConsoleInput(*this); }

        wxString GetInput(void) const
        {
            return m_input;
        }

    private:
        wxString m_input;
};

#endif // EVENTS_H_INCLUDED
