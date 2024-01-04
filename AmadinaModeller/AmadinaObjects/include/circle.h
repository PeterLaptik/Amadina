#ifndef SHAPE_CIRCLE_H
#define SHAPE_CIRCLE_H

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
		namespace shapes2D
		{
			using cad::modeller::geometry::Direction;

			class DLL_EXPORT Circle : public AbstractShape
			{
				public:
					Circle(const Point &p, double radius);
					Circle(double x, double y, double z, double radius);
					~Circle() override = default;

					void SetCenter(const Point &p);
					void SetRadius(double rad);
					void SetDirection(const Direction &dir);
					const Direction& GetDirection()const;
					const Point& GetCenter() const;
					double GetRadius() const;

				private:
					Direction m_direction;
					Point m_center;
					double m_radius;
			};
		}
	}
}

#endif

