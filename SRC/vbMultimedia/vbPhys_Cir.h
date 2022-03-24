#ifndef PHYS_CIR_H
#define PHYS_CIR_H

#include "basetypes.h"
#include "box2d/box2d.h"
#include "vbPhysicsObject.h"
#include "vbImage.h"
 
class vbPhys_Cir : public vbImage, public vbPhysicsObject
{
private:
public:
	vbPhys_Cir(b2World* _world, Vector2 _pos, FLOAT _radius, b2BodyType _type, vbContactListener* _listener);
	vbPhys_Cir(b2World* _world, Vector2 _pos, FLOAT _radius, b2BodyType _type, vbSpriteTexture* _texture, vbContactListener* _listener);
	void update();
	void draw();
	void ResetPosition(Vector2 _center); // center coordinate
	//Vector2 GetPosition(); // center coordinate
};
#endif // !PHYS_CIR_H
