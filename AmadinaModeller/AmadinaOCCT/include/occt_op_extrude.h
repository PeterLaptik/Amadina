#ifndef OCCT_OP_EXTRUDE
#define OCCT_OP_EXTRUDE

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
		namespace occt
		{
			namespace operations
			{
				using cad::modeller::AbstractOperation;

				class ExtrudeOcct: public AbstractOperation
				{
					public:
						
					private:
						
				};
			}
		}
	}
}

#endif