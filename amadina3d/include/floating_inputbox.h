#ifndef FLOATINGINPUTBOX_H
#define FLOATINGINPUTBOX_H

#include <wx/panel.h>

class FloatingInputBox: public wxPanel
{
    public:
        FloatingInputBox(wxWindow* parent,
                         wxWindowID id = wxID_ANY,
                         const wxPoint &pos = wxDefaultPosition,
                         const wxSize &size = wxSize(-1,-1),
                         long style = wxTAB_TRAVERSAL,
                         const wxString &name = wxEmptyString);

        virtual ~FloatingInputBox();

        void MoveTo(int x, int y);

    private:
        int m_last_x;
        int m_last_y;
};

#endif // FLOATINGINPUTBOX_H
