#ifndef SHAPE_LINE_INCLUDED_H
#define SHAPE_LINE_INCLUDED_H

#include "point.h"

#ifdef _WINDLL
#define DLL_EXPORT __declspec(dllexport)
#else
#define DLL_EXPORT
#endif

namespace cad::model::flat
{
    class Line : public AbstractShape
    {
        public:
            DLL_EXPORT Line(const Point &p1, const Point &p2);
            DLL_EXPORT ~Line() override = default;

            DLL_EXPORT void SetPoints(const Point &p1, const Point &p2);
            DLL_EXPORT void SetFirstPoint(const Point &p);
            DLL_EXPORT void SetSecondPoint(const Point &p);
            DLL_EXPORT const Point& GetFirstPoint() const;
            DLL_EXPORT const Point& GetSecondPoint() const;

        private:
            Point m_first;
            Point m_second;
    };
}

#endif // SHAPE_LINE_INCLUDED_H
