#ifndef PHYSICSOBJECT_H
#define PHYSICSOBJECT_H

#include "box2d/box2d.h"
#include "vbGraphicObject.h"
#include "basetypes.h"
#include "vbImage.h"

class PhysicsObject : public vbGraphicObject
{     
private:
public:
	PhysicsObject(b2World* _world, Vector2 _pos, Vector2 _size, BOOL _isStatic);
	void update();
	void render();
	b2Body* body;
	void move(Vector2 _des);
	void setPosition(Vector2 _des);
	~PhysicsObject();
};
#endif // !PHYSICSOBJECT_H
