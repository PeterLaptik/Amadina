#ifndef GEOM_DIRECTION_INCLUDED_H
#define GEOM_DIRECTION_INCLUDED_H

#ifdef _WINDLL
#define DLL_EXPORT __declspec(dllexport)
#else
#define DLL_EXPORT
#endif

namespace cad::model::geom
{
    ///\brief Represents a unit vector in 3D space
    class Direction
    {
        public:
            /// Builds a unit vector for a default Z-axis (0.0, 0.0, 1.0)
            DLL_EXPORT Direction();
            DLL_EXPORT Direction(double x, double y, double z);
            DLL_EXPORT ~Direction() = default;

            DLL_EXPORT void SetAngles(double x, double y, double z);
            DLL_EXPORT void GetAngles(double *x, double *y, double *z) const;
            DLL_EXPORT double GetX() const;
            DLL_EXPORT double GetY() const;
            DLL_EXPORT double GetZ() const;

        private:
            double m_x;
            double m_y;
            double m_z;
    };
}

#endif // GEOM_DIRECTION_INCLUDED_H



