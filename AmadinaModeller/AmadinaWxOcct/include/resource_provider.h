#ifndef RESOURCE_PROVIDER_WXVIEW_H
#define RESOURCE_PROVIDER_WXVIEW_H

#include<wx/imaglist.h>

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
			list->Add(GetBitmapFromPath("..\\share\\menu\\ico_mnu_hidden_shape.ico"));
			list->Add(GetBitmapFromPath("..\\share\\menu\\ico_mnu_error_shape.ico"));
			return list;
		}

	private:
		wxBitmap GetBitmapFromPath(const wxString &path) const
		{
			wxBitmap btm(path, wxBITMAP_TYPE_ICO);
			return btm;
		}
};

#endif // !RESOURCE_PROVIDER_WXVIEW_H

