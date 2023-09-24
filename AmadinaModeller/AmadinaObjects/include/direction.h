#ifndef SHAPE_DIRECTION_ANGLES_H
#define SHAPE_DIRECTION_ANGLES_H

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
			///\brief Represents a unit vector in 3D space
			class DLL_EXPORT Direction
			{
				public:
					/// Builds a unit vector for a default Z-axis (0.0, 0.0, 1.0)
					Direction();
					Direction(double x, double y, double z);
					~Direction() = default;

					void SetAngles(double x, double y, double z);
					double GetX() const;
					double GetY() const;
					double GetZ() const;

				private:
					double m_x;
					double m_y;
					double m_z;
			};
		}
	}
}

#endif



