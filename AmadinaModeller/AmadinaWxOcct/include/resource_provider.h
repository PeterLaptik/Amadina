#ifndef RESOURCE_PROVIDER_WXVIEW_H
#define RESOURCE_PROVIDER_WXVIEW_H

#include<wx/imaglist.h>
#include <wx/filefn.h> 

const char *const relative_path_to_images = "/share/menu/";

enum TreeMenuIcons
{
	no_icon = -1,
	ico_hidden = 0,
	ico_error = 1
};

class ResourceProvider
{
	public:
		virtual wxImageList* GetTreeMenuImageList() = 0;

};


class ResourceProviderFS: public ResourceProvider
{
	public:
		ResourceProviderFS() = default;

		wxImageList *GetTreeMenuImageList() override
		{
			wxImageList *list = new wxImageList(16, 16);
			wxString path = wxGetCwd() + relative_path_to_images;
			list->Add(GetBitmapFromPath(path + "ico_mnu_hidden_shape.ico"));
			list->Add(GetBitmapFromPath(path + "ico_mnu_error_shape.ico"));
			return list;
		}

	private:
		wxBitmap GetBitmapFromPath(const wxString &path) const
		{
			return wxBitmap(path, wxBITMAP_TYPE_ICO);
		}
};

#endif // !RESOURCE_PROVIDER_WXVIEW_H

