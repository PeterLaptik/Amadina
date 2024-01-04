#ifndef OP_BOOL_FUSE_H
#define OP_BOOL_FUSE_H

#include "abstract_operation.h"

#ifdef _WINDLL
	#define DLL_EXPORT __declspec(dllexport)
#else
	#define DLL_EXPORT
#endif

namespace cad
{
	namespace modeller
	{
		namespace operations
		{

			class OpBoolFuse : public AbstractOperation
			{
				public:
					DLL_EXPORT explicit OpBoolFuse() = default;

					DLL_EXPORT ~OpBoolFuse() override = default;

					DLL_EXPORT void AddShape(AbstractShape *shape);

					//DLL_EXPORT ShapeIterator GetShapes() const;

				private:
					std::vector<AbstractShape*> m_initial_shapes;
			};
		}
	}
}

#endif
