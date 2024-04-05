#ifndef ABSTRACT_MODEL_HISTORY_H
#define ABSTRACT_MODEL_HISTORY_H

#ifdef _WINDLL
	#define DLL_EXPORT __declspec(dllexport)
#else
	#define DLL_EXPORT
#endif

#include "abstract_shape.h"
#include <vector>

namespace cad::modeller
{
	///\brief Represents container of model items, operations and activities.
	/// ModelTree contains full subsequence of activities for buiding model.
	/// Any manipulations with ModelTree should lead to updating visualization.
	/// Item pointers transfered to ModelTree are handled by ModelTree, and should not be deleted from the outside.
	class ModelTree
	{
		public:
			DLL_EXPORT explicit ModelTree(AbstractCanvas *canvas)
				: m_canvas(canvas)
			{ }

			ModelTree(const ModelTree &) = delete;

			ModelTree &operator= (const ModelTree &) = delete;

			DLL_EXPORT virtual ~ModelTree();

			DLL_EXPORT virtual void AddItem(AbstractShape *item);

			DLL_EXPORT virtual void RemoveItem(AbstractShape *item);

			DLL_EXPORT virtual void HideItem(AbstractShape *item);

			DLL_EXPORT virtual void ShowItem(AbstractShape *item);

			DLL_EXPORT virtual void RedrawItem(AbstractShape *item);

			DLL_EXPORT virtual void RedrawTree();

			DLL_EXPORT AbstractCanvas *GetCanvas() const;

		private:
			void PurgeDependentOperations(AbstractShape *item) const;
			void UpdateDependentOperations(AbstractShape *item) const;

			AbstractCanvas *m_canvas;
			std::vector<AbstractShape *> m_shapes;
	};
}

#endif
