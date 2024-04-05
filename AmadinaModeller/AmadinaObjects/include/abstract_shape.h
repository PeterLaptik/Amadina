#ifndef ABSTRACT_SHAPE_H
#define ABSTRACT_SHAPE_H

#include "abstract_canvas.h"
#include <string>
#include <vector>

#ifdef _WINDLL
	#define DLL_EXPORT __declspec(dllexport)
#else
	#define DLL_EXPORT
#endif

namespace cad::modeller
{
	///\brief Common interface for drawable entities.
	/// Abstract shape represents any type of 2D or 3D entity which can be shown / drawn on the screen (canvas)
	class DLL_EXPORT AbstractShape
	{
		public:
			AbstractShape() = default;

			virtual ~AbstractShape() = default;

			///\brief Sets canvas which will be used for the shape visualization
			virtual void AssignCanvas(AbstractCanvas *cnv) = 0;

			///\brief Draws shape on a screen (canvas)
			virtual void Draw() = 0;

			///\brief Removes shape from a screen (canvas)
			virtual void Hide() = 0;

			///\brief Shows shape on a screen (canvas), without redrawing
			virtual void Show() = 0;

			///\brief Rebuilds and redraws shape on a screen (canvas)
			virtual void Refresh() = 0;

			///\brief Returns all sub-shapes. 
			/// The method should be overriden for composite shapes.
			///\container - vector to put results 
			virtual void GetSubObjects(std::vector<AbstractShape*> &container)
			{
				// no sub-objects by default
			}

			///\brief Sets visibility of the shape.
			/// Only visible entities are shown on a screen.
			/// In general, visibility does not affect operations results which use the entity.
			void SetVisible(bool visible)
			{
				m_is_visible = visible;
			}

			bool GetIsVisible() const
			{
				return m_is_visible;
			}

			///\brief Sets whether the shape is being used by operation.
			/// The flag can be used to forbid using shape in more than one operation.
			void SetHandled(bool is_handled)
			{
				m_is_handled = is_handled;
			}

			bool GetIsHandled() const
			{
				return m_is_handled;
			}

		private:
			bool m_is_visible = true;
			bool m_is_handled = false;
	};
}

#endif
