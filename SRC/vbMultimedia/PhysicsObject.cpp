#include "PhysicsObject.h";

PhysicsObject::PhysicsObject(b2World* _world, Vector2 _pos, Vector2 _size, BOOL _isStatic) : vbGraphicObject()
{
	_pos.x /= PPM;
	_pos.y /= PPM;
	_size.x /= PPM;
	_size.y /= PPM;

	this->isAlive = TRUE;
	b2BodyDef bodyDef;
	bodyDef.position.Set(_pos.x + _size.x / 2, _pos.y + _size.y / 2);
	//bodyDef.linearDamping = 1.0f;
	bodyDef.angularDamping = 1.0f;
	bodyDef.gravityScale = 3.0f;
	if (!_isStatic)
	{
		bodyDef.type = b2_dynamicBody;
	}
	
	this->body = _world->CreateBody(&bodyDef);
}

void PhysicsObject::update()
{
}

void PhysicsObject::render()
{

}

void PhysicsObject::move(Vector2 _new) // move relative to the current position
{
	this->body->SetTransform({ this->body->GetTransform().p.x + _new.x / PPM, this->body->GetTransform().p.y + _new.y / PPM}, this->body->GetTransform().q.GetAngle());
}

void PhysicsObject::setPosition(Vector2 _pos)
{
	this->body->SetTransform({ _pos.x / PPM, _pos.y / PPM }, this->body->GetTransform().q.GetAngle());
}

PhysicsObject::~PhysicsObject()
{
	this->body->GetWorld()->DestroyBody(this->body);
}


