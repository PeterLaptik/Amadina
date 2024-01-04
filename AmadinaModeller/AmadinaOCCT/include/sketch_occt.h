#ifndef OCCT_SKETCH_H
#define OCCT_SKETCH_H

#include "sketch.h"
#include "direction_vector.h"
#include <vector>
#include<string>

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
			using cad::modeller::shapes2D::Sketch;
			using cad::modeller::geometry::DirectionVector;

			///\brief Sketch draft assembled from 2D elements (e.g. points, lines, circles etc.)
			class SketchOcct : public Sketch
			{
				public:
					DLL_EXPORT explicit SketchOcct(const std::string &name);

					DLL_EXPORT ~SketchOcct() override = default;

					DLL_EXPORT void Draw(AbstractCanvas &cnv) final;

					DLL_EXPORT void SetDirectionVector(DirectionVector vector);

					DLL_EXPORT DirectionVector GetDirectionVector() const;


				private:
					std::string m_name;
					DirectionVector m_vector;
			};
		}
	}
}

#endif // OCCT_SKETCH_H

