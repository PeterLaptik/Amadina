#ifndef ABSTRACT_OPERATION_H
#define ABSTRACT_OPERATION_H

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
		namespace operations
		{
			///\brief Represents basic operation and its result
			class DLL_EXPORT AbstractOperation : public AbstractShape
			{
			public:
				AbstractOperation() = default;

				~AbstractOperation() override = default;

				virtual bool IsValid(void) = 0;

				virtual void Purge(const std::vector<AbstractShape*>&) = 0;
			};
		}
	}
}

#endif
