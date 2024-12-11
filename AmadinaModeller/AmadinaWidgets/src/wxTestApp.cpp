/***************************************************************
 * Name:      wxTestApp.cpp
 * Purpose:   Code for Application Class
 * Author:     ()
 * Created:   2022-07-26
 * Copyright:  ()
 * License:
 **************************************************************/

#include "wxTestApp.h"

//(*AppHeaders
#include "wxTestMain.h"
#include <wx/image.h>
//*)

IMPLEMENT_APP(wxTestApp);

bool wxTestApp::OnInit()
{
    //(*AppInitialize
    bool wxsOK = true;
    wxInitAllImageHandlers();
    if ( wxsOK )
    {
    	wxTestFrame* Frame = new wxTestFrame(0);
    	Frame->Show();
    	SetTopWindow(Frame);
    }
    //*)
    return wxsOK;

}
