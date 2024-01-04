#ifndef OP_EXTRUDE_OCCT_H
#define OP_EXTRUDE_OCCT_H

#include "op_extrude.h"

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

				using cad::modeller::operations::OpExtrude;

				class OpExtrudeOcct: public OpExtrude
				{
					public:
						OpExtrude::OpExtrude;

						DLL_EXPORT ~OpExtrudeOcct() override = default;

						DLL_EXPORT void Draw(AbstractCanvas& cnv) override;

						DLL_EXPORT bool IsValid() override;

						DLL_EXPORT void Purge(std::vector<AbstractShape*> &container) override;
				};
			}
		}
	}
}

#endif