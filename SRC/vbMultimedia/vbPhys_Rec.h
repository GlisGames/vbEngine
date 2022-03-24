#ifndef PHYS_REC_H
#define PHYS_REC_H

#include "basetypes.h"
#include "box2d/box2d.h"
#include "vbPhysicsObject.h"
#include "vbImage.h"

class vbPhys_Rec : public vbPhysicsObject, public vbImage
{
private:
public:
	vbPhys_Rec(b2World* _world, Vector2 _pos, Vector2 _size, b2BodyType _type, vbContactListener* _listener);
	vbPhys_Rec(b2World* _world, Vector2 _pos, Vector2 _size, b2BodyType _type, vbSpriteTexture* _texture, vbContactListener* _listener);
	void update();
	void draw();
	void ResetPosition(Vector2 _center);
	Vector2 GetPosition();
};
#endif // !PHYS_REC_H
