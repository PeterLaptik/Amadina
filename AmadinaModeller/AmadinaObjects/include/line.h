#ifndef SHAPE_LINE_H
#define SHAPE_LINE_H

#include "point.h"

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
			class DLL_EXPORT Line: public AbstractShape
			{
				public:
					Line(const Point &p1, const Point &p2);
					~Line() override = default;

					void SetPoints(const Point &p1, const Point &p2);
					void SetFirstPoint(const Point &p);
					void SetSecondPoint(const Point &p);
					const Point& GetFirstPoint() const;
					const Point& GetSecondPoint() const;

				private:
					Point m_first;
					Point m_second;
			};
		}
	}
}

#endif
