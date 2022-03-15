#ifndef PHYS_CIR_H
#define PHYS_CIR_H

#include "box2d/box2d.h"
#include "vbGraphicObject.h"
#include "basetypes.h"
#include "vbImage.h"
#include "PhysicsObject.h"
 
class phys_Cir : public PhysicsObject, public vbImage
{
private:
public:
	phys_Cir(b2World* _world, Vector2 _pos, FLOAT _radius, b2BodyType _type);
	phys_Cir(b2World* _world, Vector2 _pos, FLOAT _radius, b2BodyType _type, vbSpriteTexture* _texture);
	void update();
	void draw();
	void ResetPosition(Vector2 _center); // center coordinate
	//Vector2 GetPosition(); // center coordinate
};
#endif // !PHYS_CIR_H
