#include "amadin_app.h"
#include "main_frame.h"
#include <wx/image.h>

IMPLEMENT_APP(AmadinApp);

bool AmadinApp::OnInit()
{
    wxInitAllImageHandlers();
    MainFrame* frame = new MainFrame(0);
    frame->Show();
    SetTopWindow(frame);
    return true;
}
