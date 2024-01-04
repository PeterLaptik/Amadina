#include "sketch.h"
#include<algorithm>

cad::modeller::shapes2D::Sketch::~Sketch()
{
	for (auto shape : m_shapes)
		delete shape;
}

void cad::modeller::shapes2D::Sketch::AppendObject(AbstractShape *shape)
{
	m_shapes.push_back(shape);
}

void cad::modeller::shapes2D::Sketch::RemoveObject(AbstractShape *shape)
{
	std::for_each(m_shapes.begin(), m_shapes.end(),
		[=](AbstractShape *s) {
			if (s == shape)
			{
				delete s;
				s = nullptr;
			}
				
		});

	m_shapes.erase(std::remove(m_shapes.begin(), m_shapes.end(), nullptr), m_shapes.end());
}

void cad::modeller::shapes2D::Sketch::GetShapes(std::vector<AbstractShape *> &receiver) const
{
	for (auto &entity : m_shapes)
		receiver.push_back(entity);
}


