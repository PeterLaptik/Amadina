#ifndef ABSTRACT_MODEL_TREE_INCLUDED_H
#define ABSTRACT_MODEL_TREE_INCLUDED_H

#ifdef _WINDLL
#define DLL_EXPORT __declspec(dllexport)
#else
#define DLL_EXPORT
#endif

#include "abstract_shape.h"
#include <vector>

namespace cad::model
{
    ///\brief Represents container of model items, operations and activities for creating a 3D model. \n
    /// The ModelTree contains full subsequence of activities for buiding model. \n
    /// Any manipulations with ModelTree lead to updating visualization. \n
    /// Objects pointers received by ModelTree are managed by ModelTree, and should not be deleted from the outside.
    class ModelTree
    {
        public:
            DLL_EXPORT explicit ModelTree(AbstractCanvas *canvas);

            ModelTree(const ModelTree&) = delete;

            ModelTree& operator= (const ModelTree&) = delete;

            DLL_EXPORT virtual ~ModelTree();

            /// Appends and visualizes object. \n
            /// The object pointer is managed by the model tree since appending.
            DLL_EXPORT virtual void AddItem(AbstractShape *item);

            /// Removes object from the model tree and a canvas. \n
            /// A raw pointer to the object is being deleted too. \n
            /// To prevent errors caused by invalid pointer model tree calls 'Purge'-method
            /// for each object inside it. \n
            /// Read description of 'Purge'-method for AbstractOperation and its implementations for how to remove broken pointer.
            ///\see AbstractOperation
            DLL_EXPORT virtual void RemoveItem(AbstractShape *item);

            /// Removes object visualization from a canvas
            DLL_EXPORT virtual void HideItem(AbstractShape *item);

            /// Shows object visualization on a canvas
            DLL_EXPORT virtual void ShowItem(AbstractShape *item);

            /// Updates canvas visualisation of a model. \n
            /// Base implementation: calls Refresh for all shape.
            DLL_EXPORT virtual void RedrawTree();

            DLL_EXPORT AbstractCanvas* GetCanvas() const;

        private:
            void PurgeDependentOperations(AbstractShape *item) const;

            AbstractCanvas *m_canvas;
            std::vector<AbstractShape*> m_shapes;
    };
}

#endif // ABSTRACT_MODEL_TREE_INCLUDED_H
