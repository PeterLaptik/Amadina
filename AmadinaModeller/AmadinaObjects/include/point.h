#ifndef SHAPE_POINT_INCLUDED_H
#define SHAPE_POINT_INCLUDED_H

#include "abstract_shape.h"

#ifdef _WINDLL
#define DLL_EXPORT __declspec(dllexport)
#else
#define DLL_EXPORT
#endif


namespace cad::model::flat
{
    class Point : public AbstractShape
    {
        public:
            DLL_EXPORT Point();
            DLL_EXPORT Point(double x, double y, double z = 0.0);
            DLL_EXPORT ~Point() override = default;

            DLL_EXPORT void AssignCanvas(AbstractCanvas *cnv) override;
            DLL_EXPORT void DrawShape() override;
            DLL_EXPORT void RemoveShape() override;

            DLL_EXPORT void SetCoordinates(double x, double y, double z);
            DLL_EXPORT void SetX(double x);
            DLL_EXPORT void SetY(double y);
            DLL_EXPORT void SetZ(double z);

            DLL_EXPORT double GetX() const;
            DLL_EXPORT double GetY() const;
            DLL_EXPORT double GetZ() const;

            /// Returns whether the point was initialized with coordinates.
            DLL_EXPORT bool IsSet() const;

        private:
            double m_x;
            double m_y;
            double m_z;
    };
}

#endif // SHAPE_POINT_INCLUDED_H
