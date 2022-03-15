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
	else //if (_type == b2_dynamicBody)
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
	vbImage::update();
	//this->body->SetAwake(TRUE);

	this->position.x = this->body->GetPosition().x * PPM;
	this->position.y = this->body->GetPosition().y * PPM;
	this->transformed.position.x = this->body->GetPosition().x * PPM;
	this->transformed.position.y = this->body->GetPosition().y * PPM;
	this->transformed.rotation = this->body->GetAngle() * RAD2DEG;
}
 
void phys_Rec::draw()
{
	if (this->texture == NULL && this->spriteTexture == NULL)
	{
		Rectangle rec = { this->position.x, this->position.y, this->width, this->height };
		DrawRectanglePro(rec, { (float)this->width / 2, (float)this->height / 2 }, this->body->GetTransform().q.GetAngle() * RAD2DEG, WHITE);
	}
	else
	{
		//int frameWidth = this->width;
		//int frameHeight = this->height;
		//Rectangle sourceRec = { 0.0f, 0.0f, (float)frameWidth, (float)frameHeight };
		//Rectangle destRec = { this->position.x, this->position.y, this->width * this->scale, this->height * this->scale};
		//Vector2 origin = { (float)frameWidth / 2, (float)frameHeight / 2 };
 		//DrawTexturePro(*this->texture, sourceRec, destRec, origin, this->body->GetAngle() * RAD2DEG, WHITE);
		vbImage::draw();
	}
}

void phys_Rec::ResetPosition(Vector2 _center) // center coordinate
{
	this->body->SetTransform({ _center.x / PPM, _center.y / PPM }, 0);
}

Vector2 phys_Rec::GetPosition() // center coordinate
{
	return { this->body->GetTransform().p.x * PPM, this->body->GetTransform().p.y * PPM };
}


