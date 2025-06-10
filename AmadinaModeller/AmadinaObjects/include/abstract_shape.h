#ifndef ABSTRACT_SHAPE_INCLUDED_H
#define ABSTRACT_SHAPE_INCLUDED_H

#include <vector>

#ifdef _WINDLL
#define DLL_EXPORT __declspec(dllexport)
#else
#define DLL_EXPORT
#endif

namespace cad::model
{
    class AbstractCanvas;

    ///\brief Common interface for drawable entities. \n
    /// Abstract shape represents any type of 2D or 3D entity which can be shown / drawn on a screen (canvas). \n
    /// Following methods have to be overriden: AssignCanvas, DrawShape, RemoveShape, and GetSubObjects (for composite shapes).
    class AbstractShape
    {
        public:
            DLL_EXPORT AbstractShape() = default;

            DLL_EXPORT virtual ~AbstractShape() = default;

            ///\brief Sets canvas which will be used for the shape visualization. \n
            /// Holding / casting the pointer depends on a canvas and shapes implementations.
            ///\param cnv pointer to canvas implementation
            ///\see any OCCT-shapes implementations
            DLL_EXPORT virtual void AssignCanvas(AbstractCanvas *cnv) = 0;

            ///\brief Draws shape on a screen (canvas). \n
            /// Default implementation:
            /// 1. sets m_is_visible to true
            /// 2. calls DrawShape method
            ///\see DrawShape
            DLL_EXPORT virtual void Draw();

            ///\brief Removes shape from a screen (canvas). \n
            /// Default implementation: 
            /// 1. sets m_is_visible to false
            /// 2. calls RemoveShape protected method
            ///\see RemoveShape
            DLL_EXPORT virtual void Remove();

            ///\brief Rebuilds and redraws shape on a screen (canvas). \n
            /// Default implementation: calls RemoveShape + DrawShape if m_is_visible is true. \n
            /// Do nothing for m_is_visible is set to false.
            ///\see RemoveShape
            ///\see DrawShape
            DLL_EXPORT virtual void Refresh();

            ///\brief Returns all sub-shapes. \n
            /// Empty default implementation. \n
            /// The method should be overriden for composite shapes. \n
            /// TODO example
            ///\param container - vector to put results 
            DLL_EXPORT virtual void GetSubObjects(std::vector<AbstractShape *> &container);

            ///\brief Returns whether the shape is shown an a canvas
            DLL_EXPORT bool IsVisible() const;

            ///\brief Sets whether the shape is being used by operation or other object. \n
            /// The flag can be used to forbid using shape in more than one operation,
            /// or to indicate that the shape is handled by an operation. 
            ///\see any OCCT-operation implementation as an example
            DLL_EXPORT void SetHandled(bool is_handled);

            ///\see SetHandled
            DLL_EXPORT bool IsHandled() const;

        protected:
            /// Computes geometry, and draws shape on a canvas. \n
            /// Expected implementation: recalculate geometry + visualize geometry object on a canvas.
            ///\see any OCCT-shape implementation as an example
            DLL_EXPORT virtual void DrawShape() = 0;

            /// Removes shape from a canvas. \n
            /// Expected implementation: remove geometry object from a canvas.
            ///\see any OCCT - shape implementation as an example
            DLL_EXPORT virtual void RemoveShape() = 0;

            ///\brief Sets visibility of the shape. \n
            /// Only visible entities are shown on a screen. \n
            /// Expected calls: set to true / false on Draw / Remove template methods
            ///\see Draw
            ///\see Remove
            DLL_EXPORT void SetVisible(bool visible);

        private:
            bool m_is_visible = true;
            bool m_is_handled_by_operation = false;
    };
}

#endif // ABSTRACT_SHAPE_INCLUDED_H
