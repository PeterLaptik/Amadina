#ifndef ABSTRACT_CANVAS_INCLUDED_H
#define ABSTRACT_CANVAS_INCLUDED_H


#ifdef _WINDLL
#define DLL_EXPORT __declspec(dllexport)
#else
#define DLL_EXPORT
#endif


namespace cad::model
{
    ///\brief Marker interface for GUI-widgets able to show geometrical entities.
    ///\see OcctCanvas implementation as an example
    class AbstractCanvas
    {
        public:
            DLL_EXPORT AbstractCanvas() = default;

            DLL_EXPORT virtual ~AbstractCanvas() = default;
    };
}

#endif // ABSTRACT_CANVAS_INCLUDED_H
