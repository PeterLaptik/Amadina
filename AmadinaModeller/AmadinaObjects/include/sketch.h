#ifndef ABSTRACT_SKETCH_INCLUDED_H
#define ABSTRACT_SKETCH_INCLUDED_H

#include "abstract_shape.h"
#include "direction_vector.h"
#include <string>
#include <vector>

#ifdef _WINDLL
#define DLL_EXPORT __declspec(dllexport)
#else
#define DLL_EXPORT
#endif

namespace cad::model::flat
{
    using cad::model::geom::DirectionVector;

    ///\brief Base implementation of a flat sketch: object which contains a set of 2D shapes
    class Sketch : public AbstractShape
    {
        public:
            DLL_EXPORT explicit Sketch(const std::string &name);

            DLL_EXPORT ~Sketch() override;

            DLL_EXPORT virtual void AppendObject(AbstractShape *shape);

            DLL_EXPORT virtual void RemoveObject(AbstractShape *shape);

            DLL_EXPORT void SetDirectionVector(const DirectionVector &vector);

            DLL_EXPORT DirectionVector GetDirectionVector() const;

            DLL_EXPORT void GetSubObjects(std::vector<AbstractShape *> &container) override;

        protected:
            std::vector<AbstractShape *> m_shapes;
            std::string m_name;
            DirectionVector m_vector;
    };
}

#endif // ABSTRACT_SKETCH_INCLUDED_H
