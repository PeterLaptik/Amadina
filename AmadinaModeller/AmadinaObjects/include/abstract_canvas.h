#ifndef ABSTRACT_CANVAS_H
#define ABSTRACT_CANVAS_H

#ifdef _WINDLL
	#define DLL_EXPORT __declspec(dllexport)
#else
	#define DLL_EXPORT
#endif

namespace cad
{
	namespace modeller
	{
		///\brief Marker-interface for widgets able to show geometrical entities.
		/// Kernel-independent.
		///\see OcctCanvas implementation as an example
		class DLL_EXPORT AbstractCanvas
		{
			public:
				AbstractCanvas() = default;

				virtual ~AbstractCanvas() = default;
		};
	}
}

#endif
