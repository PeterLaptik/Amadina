#ifndef CAD_HISTORY_TREE
#define CAD_HISTORY_TREE

#include "abstract_shape.h"
#include "abstract_canvas.h"
#include <wx/treectrl.h>
#include <vector>
#include <map>

using cad::modeller::AbstractShape;
using cad::modeller::AbstractCanvas;

//\brief Root node of a history tree.
// Contains other nodes
class wxCadHistoryTree: public wxTreeCtrl
{
	public:
        using wxTreeCtrl::wxTreeCtrl;

        ~wxCadHistoryTree() override;

        void AppendObject(AbstractShape *shape);

        wxTreeItemId AppendNode(const wxString &text, int image = -1, int selImage = -1,
            wxTreeItemData *data = nullptr);

        void RedrawTree(cad::modeller::AbstractCanvas &cnv);

    private:
        std::vector<AbstractShape*> m_nodes;
};

#endif // CAD_HISTORY_TREE