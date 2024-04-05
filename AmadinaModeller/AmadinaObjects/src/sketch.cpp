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
	for (auto &obj : m_shapes)
	{
		if (obj == shape)
		{
			delete obj;
			obj = nullptr;
		}
	}
	
	m_shapes.erase(std::remove(m_shapes.begin(), m_shapes.end(), shape), m_shapes.end());
}

void cad::modeller::shapes2D::Sketch::GetSubObjects(std::vector<AbstractShape *> &container)
{
	for (auto &entity : m_shapes)
	{
		container.push_back(entity);
		entity->GetSubObjects(container);
	}
}


