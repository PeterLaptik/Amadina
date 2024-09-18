#ifndef WIDGET_FACTORY_H_INCLUDED
#define WIDGET_FACTORY_H_INCLUDED

#include "abstract_modeller.h"
#include <wx/window.h>

#ifdef __WXMSW__
	#define DECL_DLL_EXPORT __declspec(dllexport)
#else
	#define DECL_DLL_EXPORT
#endif

// Generates modeller panel widget
// The widget is a sub-class of wxPanel type
// Allowed operations -- see wxAbstractModeller interface
DECL_DLL_EXPORT wxAbstractModeller* get_abstract_modeller(wxWindow *parent);

#endif
