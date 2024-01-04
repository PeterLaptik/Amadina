#ifndef OP_BOOL_FUSE_OCCT_H
#define OP_BOOL_FUSE_OCCT_H

#include "op_bool_fuse.h"

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

				using cad::modeller::operations::OpBoolFuse;

				class OpBoolFuseOcct : public OpBoolFuse
				{
				public:
					OpBoolFuse::OpBoolFuse;

					DLL_EXPORT ~OpBoolFuseOcct() override = default;

					DLL_EXPORT void Draw(AbstractCanvas &cnv) override;

					DLL_EXPORT bool IsValid() override;

					DLL_EXPORT void Purge(std::vector<AbstractShape *> &container) override;

				private:

				};
			}
		}
	}
}

#endif
