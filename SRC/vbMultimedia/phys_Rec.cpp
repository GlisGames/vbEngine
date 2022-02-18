#include "phys_Rec.h"

phys_Rec::phys_Rec(b2World* _world, Vector2 _pos, Vector2 _size, BOOL _isStatic, Texture2D* _texture) : PhysicsObject(_world, _pos, _size, _isStatic)
{
	_pos.x /= PPM;
	_pos.y /= PPM;
	_size.x /= PPM;
	_size.y /= PPM;

	b2PolygonShape shape;
	shape.SetAsBox(_size.x / 2, _size.y / 2);
	if (_isStatic)
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

	this->texture = _texture;

	this->width = _size.x * PPM;
	this->height = _size.y * PPM;
	this->position.x = this->body->GetPosition().x * PPM;
	this->position.y = this->body->GetPosition().y * PPM;
}

phys_Rec::phys_Rec(b2World* _world, Vector2 _pos, Vector2 _size, BOOL _isStatic) : PhysicsObject(_world, _pos, _size, _isStatic)
{
	_pos.x /= PPM;
	_pos.y /= PPM;
	_size.x /= PPM;
	_size.y /= PPM;

	b2PolygonShape shape;
	shape.SetAsBox(_size.x / 2, _size.y / 2);

	if (_isStatic)
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

	this->texture = NULL;

	this->width = _size.x * PPM;
	this->height = _size.y * PPM;
	this->position.x = this->body->GetPosition().x * PPM;
	this->position.y = this->body->GetPosition().y * PPM;
}

void phys_Rec::update()
{
	//this->body->SetAwake(TRUE);

	this->position.x = this->body->GetPosition().x * PPM;
	this->position.y = this->body->GetPosition().y * PPM;
}
 
void phys_Rec::render()
{
	if (!this->texture)
	{
		return;
		/*Rectangle rec = { this->position.x, this->position.y, this->width, this->height };
		DrawRectanglePro(rec, { (float)this->width / 2, (float)this->height / 2 }, this->body->GetTransform().q.GetAngle() * RAD2DEG, WHITE);*/
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



