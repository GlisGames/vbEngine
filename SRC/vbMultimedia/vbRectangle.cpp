#include "vbRectangle.h"

vbRectangle::vbRectangle(Rectangle _rect)
	:vbShape(TYPE_SHAPE::RECTANGLE), rect(_rect)
{
}

vbRectangle::vbRectangle(float x, float y, float width, float height)
	: vbShape(TYPE_SHAPE::RECTANGLE), rect(Rectangle{ x, y, width, height })
{
}

vbRectangle::vbRectangle(const vbRectangle& rectangle)
	:vbShape(rectangle), rect(rectangle.rect)
{
}

vbRectangle& vbRectangle::operator=(const vbRectangle& rectangle)
{
	vbShape::operator=(rectangle);
	this->rect = rectangle.rect;

	return (*this);
}

vbRectangle::~vbRectangle()
{
}

vbRoundedDrawRectangle::vbRoundedDrawRectangle(Rectangle _rect, Color _colour, float _roundness, int _segments)
	:vbRectangle(_rect), vbRoundedDrawable(_colour, _roundness, _segments)
{

}

vbRoundedDrawRectangle::vbRoundedDrawRectangle(const vbRoundedDrawRectangle& graphic)
	: vbRectangle(graphic), vbRoundedDrawable(graphic)
{

}

vbRoundedDrawRectangle& vbRoundedDrawRectangle::operator=(const vbRoundedDrawRectangle& rectangle)
{
	vbRectangle::operator=(rectangle);
	vbRoundedDrawable::operator=(rectangle);

	return (*this);
}

vbRoundedDrawRectangle::~vbRoundedDrawRectangle()
{
}

void vbRoundedDrawRectangle::drawGraphic()
{
	DrawRectangleRounded(this->rect, this->roundness, this->segments, this->colour);
}
