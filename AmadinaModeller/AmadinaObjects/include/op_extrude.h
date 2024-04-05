#ifndef OP_EXTRUDE_H
#define OP_EXTRUDE_H

#include "abstract_operation.h"
#include "direction.h"

#ifdef _WINDLL
	#define DLL_EXPORT __declspec(dllexport)
#else
	#define DLL_EXPORT
#endif

namespace cad::modeller::operations
{
	/// Extrusion operation (extrudes from sketch)
	class DLL_EXPORT OpExtrude : public AbstractOperation
	{
		public:
			OpExtrude(AbstractShape *sketch, double length);

			~OpExtrude() override;

			void Purge(AbstractShape *removed_shape) override;

			void Update(AbstractShape *updated_shape) override;

			void SetLength(double length);
			void SetSketch(AbstractShape *sketch);

			double GetLength() const;
			AbstractShape *GetSketch() const;

		private:
			AbstractShape *m_sketch;
			double m_length;
	};
}

#endif
