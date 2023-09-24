#include "factory.h"
#include "wxmodeller3d.h"

wxAbstractModeller* get_abstract_modeller(wxWindow *parent)
{
	return new wxModeller3D(parent);
}