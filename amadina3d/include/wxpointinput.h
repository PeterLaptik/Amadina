#ifndef WXPOINTINPUT_H
#define WXPOINTINPUT_H

#include <wx/panel.h>

class wxStaticText;
class wxTextCtrl;

class wxPointInput: public wxPanel
{
    public:
        wxPointInput(wxWindow* parent,
                     wxWindowID id = wxID_ANY,
                     const wxPoint &pos = wxDefaultPosition,
                     const wxSize &size = wxSize(179,45),
                     long style = wxTAB_TRAVERSAL,
                     const wxString &name = wxEmptyString);

        virtual void MoveTo(int x, int y);

        virtual ~wxPointInput();

    private:
        int m_last_x;
        int m_last_y;
        wxStaticText *m_label;
		wxTextCtrl *m_input_box;
};

#endif // WXPOINTINPUT_H
