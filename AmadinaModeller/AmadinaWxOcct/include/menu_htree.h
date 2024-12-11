#ifndef MENU_HTREE_H
#define MENU_HTREE_H

#include <wx/menu.h>
#include <wx/imaglist.h>
#include <memory>

class MenuHTree: public wxMenu
{
	public:
		explicit MenuHTree(bool is_root_node);

		~MenuHTree() override = default;

		static const int REMOVE = 1100;
		static const int HIDE = 1101;
		static const int REFRESH_ALL = 1102;
};

#endif // MENU_HTREE_H
