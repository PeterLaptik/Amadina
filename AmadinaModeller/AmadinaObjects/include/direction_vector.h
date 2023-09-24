#ifndef SHAPE_DIRECTION_VECTOR_H
#define SHAPE_DIRECTION_VECTOR_H

#include "point.h"
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
        namespace geometry
        {
            using cad::modeller::shapes2D::Point;

            ///\brief Represents a vector in 3D space
            class DLL_EXPORT DirectionVector
            {
                public:
                    DirectionVector();
                    explicit DirectionVector(const Point &p);
                    DirectionVector(const Point &p, const Direction &dir);
                    ~DirectionVector() = default;

                    void SetStartPoint(const Point &p);
                    void SetDirection(const Direction &dir);
                    const Point& GetStartPoint() const;
                    const Direction& GetDirection() const;

                private:
                    Point m_center;
                    Direction m_direction;
            };
        }
    }
}

#endif



