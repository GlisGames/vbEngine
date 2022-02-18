#include "phys_Cir.h"

phys_Cir::phys_Cir(b2World* _world, Vector2 _pos, FLOAT _radius, BOOL _isStatic, Texture2D* _texture) : PhysicsObject(_world, _pos, { _radius, _radius }, _isStatic)
{
	_pos.x /= PPM;
	_pos.y /= PPM;
	_radius /= PPM;

	b2CircleShape shape;
	shape.m_p.SetZero();
	shape.m_radius = _radius;
	if (_isStatic)
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
	
	this->texture = _texture;
	this->width = _radius * 2 * PPM;
	this->height = _radius * 2 * PPM;
	this->position.x = this->body->GetPosition().x * PPM;
	this->position.y = this->body->GetPosition().y * PPM;
}

void phys_Cir::update()
{
	//this->body->SetAwake(TRUE);

	this->position.x = this->body->GetPosition().x * PPM;
	this->position.y = this->body->GetPosition().y * PPM;
}

void phys_Cir::render() // FIXME
{
	if (!this->texture)
	{
		return;
		//DrawCircle(this->position.x, this->position.y, 25, WHITE);
	}
	else
	{
		int frameWidth = this->width;
		int frameHeight = this->height;
		Rectangle sourceRec = { 0.0f, 0.0f, (float)frameWidth, (float)frameHeight };
		Rectangle destRec = { this->position.x, this->position.y, this->width, this->height };
		Vector2 origin = { (float)frameWidth / 2, (float)frameHeight / 2 };
		DrawTexturePro(*this->texture, sourceRec, destRec, origin, this->body->GetAngle() * RAD2DEG, WHITE);
	}
}



