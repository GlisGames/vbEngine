#include "vbShape.h"

vbShape::vbShape(const TYPE_SHAPE& type)
	:TYPE(type)
{
}

vbShape::vbShape(const vbShape& shape)
	:TYPE(shape.TYPE)
{
}

vbShape& vbShape::operator=(const vbShape& shape)
{
	const_cast<TYPE_SHAPE&>(TYPE) = shape.TYPE;

	return (*this);
}

vbShape::~vbShape()
{
}
