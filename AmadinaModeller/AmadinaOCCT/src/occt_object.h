#ifndef OCCT_OBJECT_INCLUDED_H
#define OCCT_OBJECT_INCLUDED_H

#include "occt_canvas.h"
#include <AIS_InteractiveObject.hxx>
#include <Geom_Curve.hxx>

#ifdef _WINDLL
#define DLL_EXPORT __declspec(dllexport)
#else
#define DLL_EXPORT
#endif

namespace cad::model::occt
{

    ///\breaf Common interface for objects implementation under OCCT-library. \n 
    /// Implementation of each object (line, circle, cube, etc.) should keep its AIS_InteractiveObjects inside \n 
    /// and implement this interface \n
    /// TODO example
    ///\see LineOcct as an example
    class OcctObject
    {
        public:
            DLL_EXPORT virtual ~OcctObject() = default;

            /// Sets canvas for object visualization.
            ///\see OcctCanvas
            DLL_EXPORT void AssignOcctCanvas(AbstractCanvas *cnv);

            /// Returns list of 'AIS_InteractiveObject' contained in the object
            /// TODO where used
            DLL_EXPORT virtual void GetAisInteractiveObjects(std::vector<Handle(AIS_InteractiveObject)> &container) = 0;

            /// Returns geometric curves of the object.
            /// The method is used by operations (solid operations from flat shapes, etc).
            /// Implementation can be empty, if necessary
            DLL_EXPORT virtual void ExtractGeomCurves(std::vector<Handle(Geom_Curve)> &container) = 0;

            DLL_EXPORT OcctCanvas *GetOcctCanvas() const;

        protected:
            /// Helper method for derived objects. \n
            /// Implementation: if a canvas is set, then removes shape from the canvas. \n
            /// Should be called for every inner AIS_InteractiveObject.
            ///\see LineOcct as an example (RemoveShape)
            void HideOcctObject(Handle(AIS_InteractiveObject) shape);

            /// Helper method for derived objects. \n
            /// Implementation: if a canvas is set, then adds shape into the canvas \n
            /// Should be called for every inner AIS_InteractiveObject.
            ///\see LineOcct as an example (DrawShape)
            void ShowOcctObject(Handle(AIS_InteractiveObject) shape);

        private:
            OcctCanvas *m_canvas = nullptr;
    };
}

#endif // !OCCT_OBJECT_INCLUDED_H

