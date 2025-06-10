#ifndef OP_EXTRUDE_INCLUDED_H
#define OP_EXTRUDE_INCLUDED_H

#include "abstract_operation.h"

#ifdef _WINDLL
#define DLL_EXPORT __declspec(dllexport)
#else
#define DLL_EXPORT
#endif

namespace cad::model::solid
{
    /// Extrusion operation (extrudes from sketch)
    class OpExtrude : public AbstractOperation
    {
        public:
            DLL_EXPORT OpExtrude(AbstractShape *sketch, double length);

            DLL_EXPORT ~OpExtrude() override = default;

            DLL_EXPORT void Purge(AbstractShape *removed_shape) override;

            DLL_EXPORT void Update(AbstractShape *updated_shape) override;

            DLL_EXPORT void SetLength(double length);

            DLL_EXPORT void SetSketch(AbstractShape *sketch);

            DLL_EXPORT double GetLength() const;

        protected:
            DLL_EXPORT AbstractShape *GetSketch() const;

        private:
            AbstractShape *m_sketch;
            double m_length;
    };
}

#endif // OP_EXTRUDE_INCLUDED_H
