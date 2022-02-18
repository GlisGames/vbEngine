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
	//phys_Cir(b2World* _world, Vector2 _pos, FLOAT _radius, BOOL _isStatic);
	phys_Cir(b2World* _world, Vector2 _pos, FLOAT _radius, BOOL _isStatic, Texture2D* _texture);
	void update();
	void render();
	Texture2D* texture;
};
#endif // !PHYS_CIR_H
