/***************************************************************
 * Name:      wxTestMain.h
 * Purpose:   Defines Application Frame
 * Author:     ()
 * Created:   2022-07-26
 * Copyright:  ()
 * License:
 **************************************************************/

#ifndef WXTESTMAIN_H
#define WXTESTMAIN_H

//(*Headers(wxTestFrame)
#include <wx/aui/aui.h>
#include <wx/button.h>
#include <wx/frame.h>
#include <wx/menu.h>
#include <wx/panel.h>
#include <wx/sizer.h>
#include <wx/statusbr.h>
//*)

class wxTestFrame: public wxFrame
{
    public:

        wxTestFrame(wxWindow* parent,wxWindowID id = -1);
        virtual ~wxTestFrame();

    private:

        //(*Handlers(wxTestFrame)
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        void OnButton1Click(wxCommandEvent& event);
        //*)

        //(*Identifiers(wxTestFrame)
        static const long ID_BUTTON1;
        static const long ID_PANEL2;
        static const long ID_PANEL1;
        static const long idMenuQuit;
        static const long idMenuAbout;
        static const long ID_STATUSBAR1;
        //*)

        //(*Declarations(wxTestFrame)
        wxAuiManager* AuiManager1;
        wxButton* Button1;
        wxPanel* Panel1;
        wxPanel* Panel2;
        wxStatusBar* StatusBar1;
        //*)


        DECLARE_EVENT_TABLE()
};

#endif // WXTESTMAIN_H
