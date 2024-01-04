#ifndef ABSTRACT_CANVAS_H
#define ABSTRACT_CANVAS_H

namespace cad
{
	namespace modeller
	{
		///\brief Marker-interface for GUI-widgets able to show geometrical entities.
		///\see OcctCanvas implementation as an example
		class AbstractCanvas
		{
			public:
				AbstractCanvas() = default;

				virtual ~AbstractCanvas() = default;
		};
	}
}

#endif
