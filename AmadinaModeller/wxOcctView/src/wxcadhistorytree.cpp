#include "../include/wxcadhistorytree.h"
#include "abstract_canvas.h"

using cad::modeller::AbstractCanvas;

wxCadHistoryTree::~wxCadHistoryTree()
{
	for(auto obj: m_nodes)
		delete obj;
}


void wxCadHistoryTree::AppendObject(AbstractShape *shape)
{
	wxTreeItemId root_id = GetRootItem();
	AppendItem(root_id, "X-Test");
	m_nodes.push_back(shape);
	Expand(root_id);
}

wxTreeItemId wxCadHistoryTree::AppendNode(const wxString & text, int image, int selImage, wxTreeItemData * data)
{
	wxTreeItemId root_id = GetRootItem();
	return AppendItem(this, text);
}

void wxCadHistoryTree::RedrawTree(AbstractCanvas &cnv)
{
	for(auto obj: m_nodes)
	{
		obj->Draw(cnv);
	}
}
