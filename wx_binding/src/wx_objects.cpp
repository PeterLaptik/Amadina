#include "../wx_binding.h"
#include "../classes/viewpanel.h"
#include <wx/aui/aui.h>

ViewPanel* create_screen(wxAuiNotebook *parent)
{
    return new ViewPanel(parent);
}
