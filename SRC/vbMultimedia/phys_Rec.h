#ifndef PHYS_REC_H
#define PHYS_REC_H

#include "PhysicsObject.h"
#include "box2d/box2d.h"
#include "vbGraphicObject.h"
#include "basetypes.h"
#include "vbImage.h"

class phys_Rec : public PhysicsObject, public vbImage
{
private:
public:
	phys_Rec(b2World* _world, Vector2 _pos, Vector2 _size, b2BodyType _type);
	phys_Rec(b2World* _world, Vector2 _pos, Vector2 _size, b2BodyType _type, vbSpriteTexture* _texture);
	void update();
	void draw();
	void ResetPosition(Vector2 _center);
	Vector2 GetPosition();
};
#endif // !PHYS_REC_H
