#ifndef OP_EXTRUDE_H
#define OP_EXTRUDE_H

#include "abstract_operation.h"
#include "direction.h"

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
			class DLL_EXPORT OpExtrude : public AbstractOperation
			{
				public:
					OpExtrude(AbstractShape* sketch, double length);

					~OpExtrude() override = default;

					void SetLength(double length);
					void SetSketch(AbstractShape* sketch);

					double GetLength() const;
					const AbstractShape* GetSketch() const;

				private:
					AbstractShape *m_sketch;
					double m_length;
			};
		}
	}
}

#endif
