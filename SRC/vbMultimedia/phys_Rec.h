#ifndef PHYS_REC_H
#define PHYS_REC_H

#include "PhysicsObject.h"
#include "box2d/box2d.h"
#include "vbGraphicObject.h"
#include "basetypes.h"
#include "vbImage.h"

class phys_Rec : public PhysicsObject
{
private:
public:
	phys_Rec(b2World* _world, Vector2 _pos, Vector2 _size, BOOL _isStatic);
	phys_Rec(b2World* _world, Vector2 _pos, Vector2 _size, BOOL _isStatic, Texture2D* _texture);
	Texture2D* texture;
	void update();
	void draw();
	void ResetPosition(Vector2 _center);
	Vector2 GetPosition();
};
#endif // !PHYS_REC_H
