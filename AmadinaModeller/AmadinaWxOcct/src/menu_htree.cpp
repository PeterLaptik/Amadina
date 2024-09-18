#include "menu_htree.h"

MenuHTree::MenuHTree(bool is_root_node)
{
	if (!is_root_node)
	{
		Append(REMOVE, "Remove");
		Append(HIDE, "Hide / Show");
		AppendSeparator();
	}
	Append(REFRESH_ALL, "Refresh all");
}