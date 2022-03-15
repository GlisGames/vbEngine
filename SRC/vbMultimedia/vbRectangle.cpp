#include "vbRectangle.h"

vbRectangle::vbRectangle(Rectangle _rect) 
{
	this->position.x = _rect.x;
	this->position.y = _rect.y;
	this->width = _rect.width;
	this->height = _rect.height;
}

vbRectangle::vbRectangle(float x, float y, float width, float height)
{
	this->position.x = x;
	this->position.y = y;
	this->width = width;
	this->height = height;
}

vbRectangle::vbRectangle(const vbRectangle& rectangle)
{
	memcpy(this, &rectangle, sizeof(vbRectangle));
}

vbRectangle& vbRectangle::operator=(const vbRectangle& rectangle)
{
	memcpy(this, &rectangle, sizeof(vbRectangle));
	return (*this);
}

vbRectangle::~vbRectangle()
{

}

void vbRectangle::setup()
{
	vbGraphicObject::setup();
}

void vbRectangle::update()
{
	vbGraphicObject::update();
}

void vbRectangle::draw()
{
	vbGraphicObject::draw();
	DrawRectanglePro(
		{ this->transformed.position.x, this->transformed.position.y,  (FLOAT)this->transformed.width, (FLOAT)this->transformed.height },
		{ this->position.x + (this->transformed.width/2), this->position.y + (this->transformed.height /2) },
		this->transformed.rotation, 
		this->transformed.colour
	);
}
