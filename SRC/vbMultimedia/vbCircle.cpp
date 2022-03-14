#include "vbCircle.h"

vbCircle::vbCircle(Vector2 _center, float _radius)
	:vbShape(TYPE_SHAPE::CIRCLE), center(_center), radius(_radius)
{
}

vbCircle::vbCircle(const vbCircle& circle)
	:vbShape(circle), center(circle.center), radius(circle.radius)
{

}

vbCircle& vbCircle::operator=(const vbCircle& circle)
{
	vbShape::operator=(circle);
	this->center = circle.center;
	this->radius = circle.radius;

	return (*this);
}

vbCircle::~vbCircle()
{

}

vbSingleColourCircle::vbSingleColourCircle(Vector2 _center, float _radius, Color _colour)
	:vbCircle(_center, _radius), vbSingleColourDrawable(_colour)
{
}

vbSingleColourCircle::vbSingleColourCircle(const vbSingleColourCircle& graphic)
	:vbCircle(graphic), vbSingleColourDrawable(graphic)
{
}

vbSingleColourCircle& vbSingleColourCircle::operator=(const vbSingleColourCircle& graphic)
{
	vbShape::operator=(graphic);
	vbSingleColourDrawable::operator=(graphic);

	return (*this);
}

vbSingleColourCircle::~vbSingleColourCircle()
{
}

void vbSingleColourCircle::drawGraphic()
{
	DrawCircleV(this->center, this->radius, this->colour);
}
