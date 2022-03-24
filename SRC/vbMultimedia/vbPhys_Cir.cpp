#include "vbPhys_Cir.h"
#include "vbContactListener.h"

vbPhys_Cir::vbPhys_Cir(b2World* _world, Vector2 _pos, FLOAT _radius, b2BodyType _type, vbSpriteTexture* _texture, vbContactListener* _listener) : vbPhysicsObject(_world, _pos, { _radius, _radius }, _type, _listener)
{
	_pos.x /= PPM;
	_pos.y /= PPM;
	_radius /= PPM;

	this->isAlive = TRUE;

	b2CircleShape shape;
	shape.m_p.SetZero();
	shape.m_radius = _radius;
	if (_type == b2_staticBody)
	{
		this->body->CreateFixture(&shape, 0.0f);
	}
	else 
	{
		b2FixtureDef fixtureDef;
		fixtureDef.shape = &shape;
		fixtureDef.density = 1.0f;
		fixtureDef.friction = 0.3f;
		this->body->CreateFixture(&fixtureDef);
	}
	
	this->setTexture(_texture);
	this->width = _radius * 2 * PPM;
	this->height = _radius * 2 * PPM;
	this->position.x = this->body->GetPosition().x * PPM;
	this->position.y = this->body->GetPosition().y * PPM;
}

vbPhys_Cir::vbPhys_Cir(b2World* _world, Vector2 _pos, FLOAT _radius, b2BodyType _type, vbContactListener* _listener) : vbPhysicsObject(_world, _pos, { _radius, _radius }, _type, _listener)
{
	_pos.x /= PPM;
	_pos.y /= PPM;
	_radius /= PPM;

	b2CircleShape shape;
	shape.m_p.SetZero();
	shape.m_radius = _radius;
	if (_type == b2_staticBody)
	{
		this->body->CreateFixture(&shape, 0.0f);
	}
	else 
	{
		b2FixtureDef fixtureDef;
		fixtureDef.shape = &shape;
		fixtureDef.density = 1.0f;
		fixtureDef.friction = 0.3f;
		this->body->CreateFixture(&fixtureDef);
	}

	this->width = _radius * 2 * PPM;
	this->height = _radius * 2 * PPM;
	this->position.x = this->body->GetPosition().x * PPM;
	this->position.y = this->body->GetPosition().y * PPM;
}

void vbPhys_Cir::update()
{
	this->position.x = this->body->GetPosition().x * PPM;
	this->position.y = this->body->GetPosition().y * PPM;

	vbImage::update();
	this->transformed.rotation = this->body->GetAngle() * RAD2DEG;
	this->transformed.position.x -= this->width / 2;
	this->transformed.position.y -= this->height / 2;
}

void vbPhys_Cir::draw() 
{
	if (this->spriteTexture == NULL && this->texture == NULL)
	{
		DrawCircle(this->transformed.position.x, this->transformed.position.y, this->transformed.width / 2, WHITE);
	}
	else
	{
		vbImage::draw();
	}
}

void vbPhys_Cir::ResetPosition(Vector2 _center) // center coordinate
{
	this->body->SetTransform({ _center.x / PPM, _center.y / PPM }, 0);
}



