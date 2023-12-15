#ifndef OCCT_SKETCH_H
#define OCCT_SKETCH_H

#include "sketch.h"
#include "direction_vector.h"
#include <string>
#include <memory>
#include <vector>

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

					DLL_EXPORT void AppendObject(AbstractShape *shape) final;

					DLL_EXPORT void Draw(AbstractCanvas &cnv) final;

					DLL_EXPORT void SetDirectionVector(DirectionVector vector);

					void GetShapes(std::vector<AbstractShape*> &receiver) const;

					DLL_EXPORT DirectionVector GetDirectionVector() const;


				private:
					std::string m_name;
					DirectionVector m_vector;
					std::vector<std::unique_ptr<AbstractShape>> m_shapes;
			};
		}
	}
}

#endif // OCCT_SKETCH_H

