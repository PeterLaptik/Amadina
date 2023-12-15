#include "op_extrude.h"

using cad::modeller::AbstractShape;

cad::modeller::operations::OpExtrude::OpExtrude(AbstractShape* sketch, double length)
	: m_sketch(sketch), m_length(length)
{ }

void cad::modeller::operations::OpExtrude::SetLength(double length)
{
	m_length = length;
}

void cad::modeller::operations::OpExtrude::SetSketch(AbstractShape* sketch)
{
	m_sketch = sketch;
	// TODO recompute direction
}

double cad::modeller::operations::OpExtrude::GetLength() const
{
	return m_length;
}

const AbstractShape* cad::modeller::operations::OpExtrude::GetSketch() const
{
	return m_sketch;
}