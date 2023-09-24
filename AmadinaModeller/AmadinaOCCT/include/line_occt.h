#ifndef OCCT_LINE_H
#define OCCT_LINE_H

#include "line.h"
#include "sketch_object.h"
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

				class LineOcct : public Line, public SketchObject
				{
					public:
						using Line::Line;

						DLL_EXPORT ~LineOcct() override = default;

						DLL_EXPORT void Draw(AbstractCanvas &cnv) final;

						DLL_EXPORT void GetAisInteractiveObjects(std::vector<Handle(Geom_TrimmedCurve)> &container) final;

					private:
						Handle(AIS_Line) m_line = nullptr;
				};
			}
		}
	}
}

#endif