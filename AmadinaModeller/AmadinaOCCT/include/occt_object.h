#ifndef OCCT_OBJECT_H
#define OCCT_OBJECT_H

#include "occt_canvas.h"
#include <AIS_InteractiveObject.hxx>
#include <Geom_Curve.hxx>

#ifdef _WINDLL
	#define DLL_EXPORT __declspec(dllexport)
#else
	#define DLL_EXPORT
#endif

namespace cad::modeller::occt
{

	///\breaf Common interface for all objects which can be drawn via OCCT-lirary.
	/// Each object (like line, circle, cube, etc.) appears a container for an OCCT-object / objects, and should implement this interface.
	///\see LineOcct as an example
	class DLL_EXPORT OcctObject
	{
		public:
			virtual ~OcctObject() = default;

			/// Sets canvas for OCCT-objects visualization.
			///\see OcctCanvas
			void AssignOcctCanvas(AbstractCanvas *cnv)
			{
				m_canvas = static_cast<OcctCanvas *>(cnv);
			}

			void HideOcctObject(Handle(AIS_InteractiveObject) shape)
			{
				if (!m_canvas)
					return;

				m_canvas->RemoveShape(shape);
			}

			void ShowOcctObject(Handle(AIS_InteractiveObject) shape)
			{
				if (!m_canvas)
					return;

				m_canvas->AddShape(shape);
			}

			/// Returns list of 'AIS_InteractiveObject' contained in the object
			virtual void GetAisInteractiveObjects(std::vector<Handle(AIS_InteractiveObject)> &container) = 0;

			/// Returns geometric curves of the object.
			/// Implementation can be empty, if necessary
			virtual void ExtractGeomCurves(std::vector<Handle(Geom_Curve)> &container) = 0;

			OcctCanvas *GetOcctCanvas() const
			{
				return m_canvas;
			}

		private:
			OcctCanvas *m_canvas = nullptr;
	};
}

#endif // !OCCT_OBJECT_H

