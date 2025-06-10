#ifndef OP_BOOL_INCLUDED_H
#define OP_BOOL_INCLUDED_H

#include "abstract_operation.h"
#include <vector>

#ifdef _WINDLL
#define DLL_EXPORT __declspec(dllexport)
#else
#define DLL_EXPORT
#endif

namespace cad::model::solid
{
    /// Base class for boolean operations (fuse, common, cut)
    class OpBoolean : public AbstractOperation
    {
        public:
            DLL_EXPORT OpBoolean() = default;

            DLL_EXPORT ~OpBoolean() override;

            DLL_EXPORT void AddShape(AbstractShape *shape);

            DLL_EXPORT void RemoveShape(AbstractShape *shape);

            DLL_EXPORT void Purge(AbstractShape *removing_shape) override;

            DLL_EXPORT void Update(AbstractShape *updated_shape) override;

            DLL_EXPORT void GetSubObjects(std::vector<AbstractShape *> &container) override;

            DLL_EXPORT void GetShapes(std::vector<AbstractShape *> &container) const;

            DLL_EXPORT bool DoesDependOn(AbstractShape *shape) override;

        protected:
            DLL_EXPORT int GetShapesNumber() const;

        private:
            std::vector<AbstractShape *> m_initial_shapes;
    };
}

#endif // OP_BOOL_INCLUDED_H
