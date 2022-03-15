#include "vbCircle.h"

vbCircle::vbCircle(Vector2 _center, float _radius)
	: radius(_radius)
{
}

vbCircle::vbCircle(const vbCircle& circle)
	:radius(circle.radius)
{

}

vbCircle& vbCircle::operator=(const vbCircle& circle)
{
	this->radius = circle.radius;
	return (*this);
}

vbCircle::~vbCircle()
{

}

void vbCircle::setup()
{
	vbGraphicObject::setup();
}
void vbCircle::update()
{
	vbGraphicObject::update();

}
void vbCircle::draw()
{
	vbGraphicObject::draw();
	DrawCircleV(this->transformed.position, this->radius * this->transformed.scale, this->transformed.colour);
}

