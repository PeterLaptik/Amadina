#ifndef OPERATIONS_TREE_H
#define OPERATIONS_TREE_H

#include "abstract_shape.h"
#include <vector>

#ifdef _WINDLL
	#define DLL_EXPORT __declspec(dllexport)
#else
	#define DLL_EXPORT
#endif

namespace cad
{
	namespace modeller
	{
		using cad::modeller::AbstractShape;

		class OperationsTree
		{
			public:
				DLL_EXPORT OperationsTree() = default;

				DLL_EXPORT virtual ~OperationsTree();

				DLL_EXPORT virtual void AddObject(AbstractShape* object);

			private:
				std::vector<AbstractShape*> m_objects;
		};
	}
}

#endif

