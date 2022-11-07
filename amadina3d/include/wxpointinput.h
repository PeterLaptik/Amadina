#ifndef WXPOINTINPUT_H
#define WXPOINTINPUT_H

#include "floating_inputbox.h"

class wxStaticText;
class wxTextCtrl;

class wxPointInput: public FloatingInputBox
{
    public:
        wxPointInput(wxWindow* parent);

        virtual void MoveTo(int x, int y);

        virtual ~wxPointInput();

    private:

        wxStaticText *m_label;
		wxTextCtrl *m_input_box;
};

#endif // WXPOINTINPUT_H
