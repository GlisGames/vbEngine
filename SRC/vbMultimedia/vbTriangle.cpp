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

vbSingleColourTriangle::vbSingleColourTriangle(TrianglePoints _points, Color _colour)
	:vbTriangle(_points), vbSingleColourDrawable(_colour)
{
}

vbSingleColourTriangle::vbSingleColourTriangle(const vbSingleColourTriangle& graphic)
	:vbTriangle(graphic), vbSingleColourDrawable(graphic)
{
}

vbSingleColourTriangle& vbSingleColourTriangle::operator=(const vbSingleColourTriangle& graphic)
{
	vbTriangle::operator=(graphic);
	vbSingleColourDrawable::operator=(graphic);

	return (*this);
}

vbSingleColourTriangle::~vbSingleColourTriangle()
{
}

void vbSingleColourTriangle::drawGraphic()
{
	DrawTriangle(this->points[0], this->points[1], this->points[2], this->colour);
}
