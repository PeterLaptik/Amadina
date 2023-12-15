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

		class OperationNode
		{
			public:
				DLL_EXPORT explicit OperationNode(AbstractShape *m_object)
					: m_object(m_object)
				{ }

				OperationNode(const OperationNode&) = delete;

				OperationNode& operator=(const OperationNode&) = delete;

				DLL_EXPORT virtual ~OperationNode()
				{
					delete m_object;
				}



			private:
				AbstractShape *m_object;
		};
	}
}

#endif

