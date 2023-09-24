#ifndef WXMODELLER_ABSTRACT_H
#define WXMODELLER_ABSTRACT_H

#include <wx/panel.h>

class wxAbstractModeller: public wxPanel
{
	public:
        wxAbstractModeller(wxWindow *parent, wxWindowID winid, const wxPoint &pos,
                            const wxSize &size, long style, const wxString &name)
            : wxPanel(parent, winid, pos, size, style, name)
        { }

        virtual void RefreshView(void) = 0;

		virtual void Test(void) = 0;
};

#endif
