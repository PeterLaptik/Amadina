#ifndef ABSTRACT_CANVAS_H
#define ABSTRACT_CANVAS_H


#ifdef _WINDLL
	#define DLL_EXPORT __declspec(dllexport)
#else
	#define DLL_EXPORT
#endif


namespace cad::modeller
{
	class AbstractShape;

	///\brief Marker interface for GUI-widgets able to show geometrical entities.
	///\see OcctCanvas implementation as an example
	class AbstractCanvas
	{
		public:
			AbstractCanvas() = default;

			virtual ~AbstractCanvas() = default;

			virtual void ClearAll() = 0;
	};
}

#endif
