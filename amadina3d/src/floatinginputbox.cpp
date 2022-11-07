#include "floating_inputbox.h"

const int SMOOTH_COEFFICIENT = 5;
const int SQUARE_MARGIN = 5;

FloatingInputBox::FloatingInputBox(wxWindow *parent,
                           wxWindowID id,
                           const wxPoint &pos,
                           const wxSize &size,
                           long style,
                           const wxString &name)
        : wxPanel(parent, id, pos, size, style, name),
            m_last_x(-1), m_last_y(-1)
{ }

FloatingInputBox::~FloatingInputBox()
{ }

void FloatingInputBox::MoveTo(int x, int y)
{
    int delta_x = abs(x - m_last_x);
    int delta_y = abs(y - m_last_y);
    if(delta_x < SMOOTH_COEFFICIENT && delta_y < SMOOTH_COEFFICIENT)
        return;

    return;
    wxSize sz = GetSize();
    int height = sz.GetHeight();
    int width = sz.GetWidth();
    SetPosition(wxPoint(x + SQUARE_MARGIN, y - height/2));
}
