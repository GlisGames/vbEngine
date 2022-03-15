#ifndef VB_CIRCLE_H
#define VB_CIRCLE_H

#include "raylib.h"
#include "vbShape.h"
#include "vbGraphicObject.h"

class vbCircle : public vbGraphicObject
{
public:
	vbCircle(Vector2 _center, float _radius);
	vbCircle(const vbCircle& circle);
	vbCircle& operator=(const vbCircle& circle);
	virtual ~vbCircle();
	virtual void setup();
	virtual void update();
	virtual void draw();
	float radius;
};

#endif