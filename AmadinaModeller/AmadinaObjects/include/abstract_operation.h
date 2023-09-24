#ifndef ABSTRACT_OPERATION_H
#define ABSTRACT_OPERATION_H

#include "abstract_shape.h"

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

		///\brief Abstract operation represents an interface for operation leading to creating solids or surfaces
		class AbstractOperation: public AbstractShape
		{
			public:
				DLL_EXPORT AbstractOperation() = default;

				DLL_EXPORT ~AbstractOperation() override = default;


		};
	}
}

#endif