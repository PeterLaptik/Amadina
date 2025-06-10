#ifndef SHAPE_CIRCLE_INCLUDED_H
#define SHAPE_CIRCLE_INCLUDED_H

#include "point.h"
#include "direction.h"

#ifdef _WINDLL
#define DLL_EXPORT __declspec(dllexport)
#else
#define DLL_EXPORT
#endif

namespace cad::model::flat
{
    using cad::model::geom::Direction;

    class Circle : public AbstractShape
    {
        public:
            DLL_EXPORT Circle(const Point &p, double radius);
            DLL_EXPORT Circle(double x, double y, double z, double radius);
            DLL_EXPORT ~Circle() override = default;

            DLL_EXPORT void SetCenter(const Point &p);
            DLL_EXPORT void SetRadius(double rad);
            DLL_EXPORT void SetDirection(const Direction &dir);
            DLL_EXPORT const Direction &GetDirection()const;
            DLL_EXPORT const Point &GetCenter() const;
            DLL_EXPORT double GetRadius() const;

        private:
            Direction m_direction;
            Point m_center;
            double m_radius;
    };
}

#endif // SHAPE_CIRCLE_INCLUDED_H

