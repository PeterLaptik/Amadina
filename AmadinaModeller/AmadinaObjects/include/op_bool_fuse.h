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

			class DLL_EXPORT OpBoolFuse : public AbstractOperation
			{
				public:
					explicit OpBoolFuse(std::vector<AbstractShape*> &&shapes);

					~OpBoolFuse() override = default;

					const std::vector<AbstractShape *>& GetShapes() const;

				private:
					std::vector<AbstractShape *> m_initial_shapes;
			};
		}
	}
}

#endif
