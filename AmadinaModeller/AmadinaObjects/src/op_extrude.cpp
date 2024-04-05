#include "op_extrude.h"

using cad::modeller::AbstractShape;

cad::modeller::operations::OpExtrude::OpExtrude(AbstractShape* sketch, double length)
	: m_sketch(sketch), m_length(length)
{ 
	if(sketch)
		sketch->SetHandled(true);
}

cad::modeller::operations::OpExtrude::~OpExtrude()
{
	// TODO RECHECK
	//if (m_sketch)
		//m_sketch->SetHandled(false);
}

void cad::modeller::operations::OpExtrude::Purge(AbstractShape *removed_shape)
{
	AbstractShape *sketch = GetSketch();
	if (sketch == nullptr)
		return;

	if (removed_shape == sketch)
	{
		SetSketch(nullptr);
		Refresh();
		return;
	}

	std::vector<AbstractShape *> sub_shapes;
	sketch->GetSubObjects(sub_shapes);
	for (auto shape : sub_shapes)
	{
		if (shape == removed_shape)
		{
			Refresh();
			return;
		}
	}
}

void cad::modeller::operations::OpExtrude::Update(AbstractShape *updated_shape)
{
	AbstractShape *sketch = GetSketch();
	if (sketch == nullptr)
		return;

	if (updated_shape == sketch)
	{
		Refresh();
		return;
	}

	std::vector<AbstractShape *> sub_shapes;
	sketch->GetSubObjects(sub_shapes);
	for (auto shape : sub_shapes)
	{
		if (shape == updated_shape)
		{
			Refresh();
			return;
		}
	}
}

void cad::modeller::operations::OpExtrude::SetLength(double length)
{
	m_length = length;
}

void cad::modeller::operations::OpExtrude::SetSketch(AbstractShape* sketch)
{
	if (m_sketch)
		m_sketch->SetHandled(false);

	m_sketch = sketch;

	if(m_sketch)
		m_sketch->SetHandled(true);
	// TODO recompute direction
}

double cad::modeller::operations::OpExtrude::GetLength() const
{
	return m_length;
}

AbstractShape* cad::modeller::operations::OpExtrude::GetSketch() const
{
	return m_sketch;
}