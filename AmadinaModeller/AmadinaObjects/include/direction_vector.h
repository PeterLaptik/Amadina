#ifndef GEOM_DIRECTION_VECTOR_INCLUDED_H
#define GEOM_DIRECTION_VECTOR_INCLUDED_H

#include "point.h"
#include "direction.h"

#ifdef _WINDLL
#define DLL_EXPORT __declspec(dllexport)
#else
#define DLL_EXPORT
#endif

namespace cad::model::geom
{
    using cad::model::flat::Point;

    ///\brief Represents a vector in 3D space
    class DirectionVector
    {
        public:
            DLL_EXPORT DirectionVector();
            DLL_EXPORT explicit DirectionVector(const Point &p);
            DLL_EXPORT DirectionVector(const Point &p, const Direction &dir);
            DLL_EXPORT ~DirectionVector() = default;

            DLL_EXPORT void SetStartPoint(const Point &p);
            DLL_EXPORT void SetDirection(const Direction &dir);
            DLL_EXPORT const Point &GetStartPoint() const;
            DLL_EXPORT const Direction &GetDirection() const;

        private:
            Point m_center;
            Direction m_direction;
    };
}

#endif // GEOM_DIRECTION_VECTOR_INCLUDED_H



