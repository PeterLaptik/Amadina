#ifndef OP_BOOL_COMMON_OCCT_H
#define OP_BOOL_COMMON_OCCT_H

#include "op_bool_occt.h"
#include "occt_object.h"
#include <AIS_Shape.hxx>

#ifdef _WINDLL
	#define DLL_EXPORT __declspec(dllexport)
#else
	#define DLL_EXPORT
#endif

namespace cad::modeller::occt::operations
{

	using cad::modeller::operations::OpBoolean;

	class OpBoolCommonOcct : public OpBoolOcct
	{
		public:
			OpBoolOcct::OpBoolOcct;

			DLL_EXPORT ~OpBoolCommonOcct() final = default;

			DLL_EXPORT void Draw() final;
	};
}

#endif

