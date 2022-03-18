#include "phys_Rec.h"

phys_Rec::phys_Rec(b2World* _world, Vector2 _pos, Vector2 _size, b2BodyType _type, vbSpriteTexture* _texture) : PhysicsObject(_world, _pos, _size, _type)
{
	_pos.x /= PPM;
	_pos.y /= PPM;
	_size.x /= PPM;
	_size.y /= PPM;

	b2PolygonShape shape;
	shape.SetAsBox(_size.x / 2, _size.y / 2);
	if (_type == b2_staticBody)
	{
		b2FixtureDef fixtureDef;
		fixtureDef.shape = &shape;
		fixtureDef.density = 0.0f;
		//fixtureDef.restitution = 1.5f;
		//fixtureDef.restitutionThreshold = 1.0f;
		this->body->CreateFixture(&fixtureDef);
	}
	else
	{
		b2FixtureDef fixtureDef;
		fixtureDef.shape = &shape;
		fixtureDef.density = 5.0f;
		fixtureDef.friction = 0.5f;

		this->body->CreateFixture(&fixtureDef);
	}

	this->setTexture(_texture);

	this->width = _size.x * PPM;
	this->height = _size.y * PPM;
	this->position.x = this->body->GetPosition().x * PPM;
	this->position.y = this->body->GetPosition().y * PPM;
}

phys_Rec::phys_Rec(b2World* _world, Vector2 _pos, Vector2 _size, b2BodyType _type) : PhysicsObject(_world, _pos, _size, _type)
{
	_pos.x /= PPM;
	_pos.y /= PPM;
	_size.x /= PPM;
	_size.y /= PPM;

	b2PolygonShape shape;
	shape.SetAsBox(_size.x / 2, _size.y / 2);

	if (_type == b2_staticBody)
	{
		this->body->CreateFixture(&shape, 0.0f);
	}
	else
	{
		b2FixtureDef fixtureDef;
		fixtureDef.shape = &shape;
		fixtureDef.density = 5.0f;
		fixtureDef.friction = 0.5f;

		this->body->CreateFixture(&fixtureDef);
	}

	this->width = _size.x * PPM;
	this->height = _size.y * PPM;
	this->position.x = this->body->GetPosition().x * PPM;
	this->position.y = this->body->GetPosition().y * PPM;
}

void phys_Rec::update()
{
	this->position.x = this->body->GetPosition().x * PPM;
	this->position.y = this->body->GetPosition().y * PPM;

	vbImage::update();
	this->transformed.rotation = this->body->GetAngle() * RAD2DEG;
	this->transformed.position.x -= this->width / 2;
	this->transformed.position.y -= this->height / 2;

}
 
void phys_Rec::draw()
{
	if (this->texture == NULL && this->spriteTexture == NULL)
	{
		Rectangle rec = { (FLOAT)this->transformed.position.x, (FLOAT)this->transformed.position.y, (FLOAT)this->width, (FLOAT)this->height };
		DrawRectanglePro(rec, { 0,0 }, this->body->GetTransform().q.GetAngle() * RAD2DEG, WHITE);
	}
	else
	{
		vbImage::draw();
	}
}

void phys_Rec::ResetPosition(Vector2 _center) // center coordinate
{
	this->body->SetTransform({ _center.x / PPM, _center.y / PPM }, 0);
}



