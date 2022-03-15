#include "vbTriangle.h"

vbTriangle::vbTriangle(TrianglePoints _points)
	:vbShape(TYPE_SHAPE::TRIANGLE), points(_points)
{
}

vbTriangle::vbTriangle(const vbTriangle& triangle)
	:vbShape(triangle), points(triangle.points)
{
}

vbTriangle& vbTriangle::operator=(const vbTriangle& triangle)
{
	vbShape::operator=(triangle);

	this->points = triangle.points;

	return (*this);
}

vbTriangle::~vbTriangle()
{
}
