#ifndef SHAPE_POINT_H
#define SHAPE_POINT_H

#include "abstract_shape.h"

#ifdef _WINDLL
	#define DLL_EXPORT __declspec(dllexport)
#else
	#define DLL_EXPORT
#endif


namespace cad::modeller::shapes2D
{
	class DLL_EXPORT Point : public AbstractShape
	{
		public:
			Point(double x, double y, double z = 0.0);
			~Point() override = default;

			void AssignCanvas(AbstractCanvas *cnv) override;
			void Draw() override;
			void Hide() override;
			void Show() override;
			void Refresh() override;

			void SetCoordinates(double x, double y, double z);
			void SetX(double x);
			void SetY(double y);
			void SetZ(double z);

			double GetX() const;
			double GetY() const;
			double GetZ() const;

		private:
			double m_x;
			double m_y;
			double m_z;
	};
}

#endif
