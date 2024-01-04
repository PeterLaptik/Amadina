#ifndef OCCT_LINE_H
#define OCCT_LINE_H

#include "line.h"
#include "occt_object_container.h"
#include <AIS_Line.hxx>

#ifdef _WINDLL
	#define DLL_EXPORT __declspec(dllexport)
#else
	#define DLL_EXPORT
#endif

namespace cad
{
	namespace modeller
	{
		namespace occt
		{
			namespace shapes2D
			{
				using cad::modeller::shapes2D::Line;

				class LineOcct : public Line, public OcctObjectContainer
				{
					public:
						using Line::Line;

						DLL_EXPORT ~LineOcct() override = default;

						DLL_EXPORT void Draw(AbstractCanvas &cnv) final;

						DLL_EXPORT void ExtractGeomCurves(std::vector<Handle(Geom_Curve)> &container) final;

						DLL_EXPORT void GetAisInteractiveObjects(std::vector<Handle(AIS_InteractiveObject)> &container) final;
					
					private:
						Handle(AIS_Line) m_line = nullptr;
				};
			}
		}
	}
}

#endif