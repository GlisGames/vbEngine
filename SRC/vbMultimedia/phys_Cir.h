#ifndef PHYS_CIR_H
#define PHYS_CIR_H

#include "box2d/box2d.h"
#include "vbGraphicObject.h"
#include "basetypes.h"
#include "vbImage.h"
#include "PhysicsObject.h"
 
class phys_Cir : public PhysicsObject
{
private:
public:
	phys_Cir(b2World* _world, Vector2 _pos, FLOAT _radius, b2BodyType _type);
	phys_Cir(b2World* _world, Vector2 _pos, FLOAT _radius, b2BodyType _type, Texture2D* _texture);
	void update();
	void draw();
	Texture2D* texture = NULL;
	void ResetPosition(Vector2 _center); // center coordinate
	Vector2 GetPosition(); // center coordinate
};
#endif // !PHYS_CIR_H
