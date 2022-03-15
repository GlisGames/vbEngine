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
	PhysicsObject(b2World* _world, Vector2 _pos, Vector2 _size, b2BodyType _type);
	void update();
	void draw();
	b2Body* body;
	void move(Vector2 _des);
	Vector2 GetPosition();
	~PhysicsObject();
};
#endif // !PHYSICSOBJECT_H
