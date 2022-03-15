#include "PhysicsObject.h";

PhysicsObject::PhysicsObject(b2World* _world, Vector2 _pos, Vector2 _size, b2BodyType _type)
{
	_pos.x /= PPM;
	_pos.y /= PPM;
	_size.x /= PPM;
	_size.y /= PPM;

	b2BodyDef bodyDef;
	bodyDef.position.Set(_pos.x + _size.x / 2, _pos.y + _size.y / 2);
	//bodyDef.linearDamping = 1.0f;
	bodyDef.angularDamping = 1.0f;
	bodyDef.gravityScale = 3.0f; 

	bodyDef.type = _type;
		
	this->body = _world->CreateBody(&bodyDef);
}

void PhysicsObject::move(Vector2 _new) // move relative to the current position
{
	this->body->SetTransform({ this->body->GetTransform().p.x + _new.x / PPM, this->body->GetTransform().p.y + _new.y / PPM}, this->body->GetTransform().q.GetAngle());
}

Vector2 PhysicsObject::GetPosition() // center coordinate
{
	return { this->body->GetTransform().p.x * PPM, this->body->GetTransform().p.y * PPM };
}

PhysicsObject::~PhysicsObject()
{
	this->body->GetWorld()->DestroyBody(this->body);
}


