#ifndef SHAPE_ITERATOR_H
#define SHAPE_ITERATOR_H

#include "abstract_shape.h"
#include <vector>

#ifdef _WINDLL
	#define DLL_EXPORT __declspec(dllexport)
#else
	#define DLL_EXPORT
#endif

namespace cad
{
	namespace modeller
	{
		class DLL_EXPORT ShapeIterator
		{
			public:
				explicit ShapeIterator(std::vector<AbstractShape*> shapes)
				{
					m_cursor = -1;
					m_size = static_cast<int>(shapes.size());
					m_shape_array = m_size > 0 ? &shapes[0] : nullptr;
				}

				~ShapeIterator() = default;

				bool More() const
				{
					return m_cursor < m_size - 1;
				}

				void Next()
				{
					++m_cursor;
				}

				AbstractShape* Value()
				{
					return m_shape_array[m_cursor];
				}

			private:
				AbstractShape **m_shape_array;
				int m_cursor;
				int m_size;
		};
	}
}

#endif

