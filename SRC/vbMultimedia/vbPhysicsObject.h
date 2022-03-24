#ifndef PHYSICSOBJECT_H
#define PHYSICSOBJECT_H

#include "basetypes.h"
#include "box2d/box2d.h"

class vbContactListener;

class vbPhysicsObject
{     
private:
public:
	vbPhysicsObject(b2World* _world, Vector2 _pos, Vector2 _size, b2BodyType _type, vbContactListener* _listener);
	b2Body* body;
	void move(Vector2 _des);
	Vector2 GetPosition();
	~vbPhysicsObject();
	void EnableContactListener(vbContactListener* _listener);
	void DisableContactListener(vbContactListener* _listener);
	BOOL phys_enabled = TRUE;
	virtual void BeginContact(b2Contact* contact) {};
	virtual void EndContact(b2Contact* contact) {};
};

#endif // !PHYSICSOBJECT_H
