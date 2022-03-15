#include "phys_Cir.h"

phys_Cir::phys_Cir(b2World* _world, Vector2 _pos, FLOAT _radius, b2BodyType _type, vbSpriteTexture* _texture) : PhysicsObject(_world, _pos, { _radius, _radius }, _type)
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
	else //if (_type == b2_dynamicBody)
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

phys_Cir::phys_Cir(b2World* _world, Vector2 _pos, FLOAT _radius, b2BodyType _type) : PhysicsObject(_world, _pos, { _radius, _radius }, _type)
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
	else //if (_type == b2_dynamicBody)
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

void phys_Cir::update()
{
	vbImage::update();
	this->position.x = this->body->GetPosition().x * PPM;
	this->position.y = this->body->GetPosition().y * PPM;

	this->transformed.position.x = this->body->GetPosition().x * PPM;
	this->transformed.position.y = this->body->GetPosition().y * PPM;
	this->transformed.rotation = this->body->GetAngle() * RAD2DEG;
	//this->body->SetAwake(TRUE);
}

void phys_Cir::draw() // FIXME
{
	if (this->spriteTexture == NULL && this->texture == NULL)
	{
		DrawCircle(this->transformed.position.x, this->transformed.position.y, this->transformed.width / 2, WHITE);
	}
	else
	{
		//int frameWidth = this->width;
		//int frameHeight = this->height;
		//Rectangle sourceRec = { 0.0f, 0.0f, (float)frameWidth, (float)frameHeight };
		//Rectangle destRec = { this->position.x, this->position.y, this->width, this->height };
		//Vector2 origin = { (float)frameWidth / 2, (float)frameHeight / 2 };
//		DrawTexturePro(*this->texture, sourceRec, destRec, origin, this->body->GetAngle() * RAD2DEG, WHITE);
		vbImage::draw();
	}
}

void phys_Cir::ResetPosition(Vector2 _center) // center coordinate
{
	this->body->SetTransform({ _center.x / PPM, _center.y / PPM }, 0);
}

//Vector2 phys_Cir::GetPosition() // center coordinate
//{
//	return { this->body->GetTransform().p.x * PPM, this->body->GetTransform().p.y * PPM };
//}


