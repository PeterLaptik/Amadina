#include "wxmodeltree.h"
#include "menu_htree.h"
#include "resource_provider.h"
#include "occt_canvas.h"
#include "sketch_occt.h"
#include "op_extrude_occt.h"
#include "op_bool_fuse_occt.h"
#include "op_bool_common_occt.h"
#include <map>
#include <wx/event.h>

using cad::modeller::AbstractCanvas;
using cad::modeller::operations::AbstractOperation;
using cad::modeller::occt::OcctCanvas;
using cad::modeller::occt::OcctObject;


wxBEGIN_EVENT_TABLE(wxModelTree, wxTreeCtrl)
	EVT_TREE_ITEM_RIGHT_CLICK(wxID_ANY, OnItemRightClick)
wxEND_EVENT_TABLE()


// State icons


// Default name prefixes dependent on object types
static const std::map<std::string, wxString> object_visible_names = {
	{typeid(cad::modeller::occt::SketchOcct).name(), "Sketch_"},
	{typeid(cad::modeller::occt::operations::OpExtrudeOcct).name(), "Extrude_"},
	{typeid(cad::modeller::occt::operations::OpBoolFuseOcct).name(), "Union_"},
	{typeid(cad::modeller::occt::operations::OpBoolCommonOcct).name(), "Intersect_"}
};


wxModelTree::wxModelTree(wxWindow *parent, AbstractCanvas *canvas)
	: wxTreeCtrl(parent), ModelTree(canvas)
{
	// TODO: correct for test / release
	ResourceProviderFS prv;
	AssignImageList(prv.GetTreeMenuImageList());
}

void wxModelTree::AddItem(AbstractShape *shape)
{
	wxString node_name = GenerateName(shape);
	AddItem(shape, node_name);
}

void wxModelTree::AddItem(AbstractShape *shape, const wxString &name)
{
	wxTreeItemId root_id = GetRootItem();

	AppendItem(root_id, name, -1, -1, new wxCadTreeData(shape, name));
	Expand(root_id);

	ModelTree::AddItem(shape);
	UpdateIcons();
}

void wxModelTree::RemoveItem(AbstractShape *item)
{
	ModelTree::RemoveItem(item);
	wxTreeCtrl::Delete(GetSelection());
	UpdateIcons();
}

void wxModelTree::HideItem(AbstractShape *item)
{
	if (item->GetIsVisible())
		ModelTree::HideItem(item);
	else
		ModelTree::ShowItem(item);

	UpdateIcons();
}

void wxModelTree::OnItemRightClick(wxTreeEvent &event)
{
	wxTreeItemId id = event.GetItem();
	SelectItem(id);

	MenuHTree mnu(GetRootItem().GetID() == id);
	mnu.SetTitle(GetItemText(id));
	mnu.Connect(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(wxModelTree::OnPopupMenuClick), NULL, this);
	PopupMenu(&mnu);
}

void wxModelTree::OnPopupMenuClick(wxCommandEvent &evt)
{
	int menu_id = evt.GetId();
	if (menu_id == MenuHTree::REFRESH_ALL)
	{
		RedrawTree();
		UpdateIcons();
		return;
	}

	wxTreeItemId item_id = GetSelection();
	if (!item_id.IsOk())
		return;

	wxTreeItemData *data = GetItemData(item_id);
	auto const *cad_data = dynamic_cast<wxCadTreeData*>(data);
	if (!cad_data)
		return;

	AbstractShape *shape = cad_data->GetShape();
	switch (menu_id) 
	{
		case MenuHTree::HIDE:
			HideItem(shape);
			break;
		case MenuHTree::REMOVE:
			RemoveUnusedName(cad_data->GetName());
			RemoveItem(shape);
			break;
		default:
			// do nothing
			break;
	}
}

void wxModelTree::UpdateIcons()
{
	wxTreeItemIdValue cookie;
	wxTreeItemId child = GetFirstChild(GetRootItem(), cookie);
	while (child.IsOk())
	{
		wxTreeItemData *data = GetItemData(child);
		auto const *cad_data = dynamic_cast<wxCadTreeData *>(data);
		if (!cad_data)
			return;

		auto obj = cad_data->GetShape();
		if (obj->GetIsVisible())
		{
			SetItemImage(child, -1);
		}
		else
		{
			SetItemImage(child, 0);
		}

		if (auto occt_obj = dynamic_cast<AbstractOperation*>(obj); occt_obj && !occt_obj->IsValid())
			SetItemImage(child, 1);

		child = GetNextChild(child, cookie);
	}
}

bool wxModelTree::IsObjectHidden(AbstractShape *shape) const
{
	auto *cnv = GetCanvas();
	auto *occt_cnv = dynamic_cast<OcctCanvas*>(cnv);
	auto *occt_object = dynamic_cast<OcctObject*>(shape);

	std::vector<Handle(AIS_InteractiveObject)> objects;
	occt_object->GetAisInteractiveObjects(objects);
	return !occt_cnv->ContainsShapes(objects);
}

wxString wxModelTree::GenerateName(const AbstractShape* const shape)
{
	std::string shape_type_name = typeid(*shape).name();
	auto shape_name_it = object_visible_names.find(shape_type_name);

	wxString shape_name = shape_name_it != object_visible_names.end() ? shape_name_it->second : wxString("Shape_");

	int shape_counter = 1;
	wxString visible_name = shape_name + wxString::Format(wxT("%i"), shape_counter);
	while (m_used_names.find(visible_name) != m_used_names.end())
	{
		++shape_counter;
		visible_name = shape_name + wxString::Format(wxT("%i"), shape_counter);
	}

	m_used_names.insert(visible_name);
	return visible_name;
}

void wxModelTree::RemoveUnusedName(const wxString &name)
{
	auto it = m_used_names.find(name);
	if (it != m_used_names.end())
		m_used_names.erase(it);
}

