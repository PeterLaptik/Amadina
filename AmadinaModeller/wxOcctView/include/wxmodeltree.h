#ifndef CAD_HISTORY_TREE
#define CAD_HISTORY_TREE

#include "abstract_shape.h"
#include "abstract_canvas.h"
#include "model_tree.h"
#include <wx/treectrl.h>
#include <vector>
#include <set>
#include <map>

using cad::modeller::AbstractShape;
using cad::modeller::AbstractCanvas;
using cad::modeller::ModelTree;

///\brief Visual model tree representation as a wxWidgets widget
class wxModelTree: public wxTreeCtrl, public ModelTree
{
	public:
        wxModelTree(wxWindow *parent, AbstractCanvas *canvas);

        ~wxModelTree() override = default;

        void AddItem(AbstractShape *shape) override;

        void AddItem(AbstractShape *shape, const wxString &name);

        void RemoveItem(AbstractShape *item) override;

        void HideItem(AbstractShape *item) override;

    private:
        void OnItemRightClick(wxTreeEvent &event);
        void OnPopupMenuClick(wxCommandEvent &evt);

        void UpdateIcons();
        bool IsObjectHidden(AbstractShape *shape) const;
        wxString GenerateName(const AbstractShape * const shape);
        void RemoveUnusedName(const wxString &name);

        std::set<wxString> m_used_names;
        std::unique_ptr<wxImageList> m_images_list;

     DECLARE_EVENT_TABLE()
};


class wxCadTreeData: public wxTreeItemData
{
    public:
        explicit wxCadTreeData(AbstractShape *shape, const wxString &name)
            : m_associated_shape(shape), m_name(name)
        { }

        ~wxCadTreeData() override = default;

        AbstractShape* GetShape() const
        {
            return m_associated_shape;
        }

        wxString GetName() const
        {
            return m_name;
        }

    private:
        AbstractShape *m_associated_shape;
        wxString m_name;
};

#endif // CAD_HISTORY_TREE