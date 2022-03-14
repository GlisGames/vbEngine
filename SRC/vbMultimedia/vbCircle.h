#ifndef VB_CIRCLE_H
#define VB_CIRCLE_H

#include "raylib.h"
#include "vbShape.h"
#include "vbGraphicDrawable.h"

class vbCircle : public vbShape
{
public:
	vbCircle(Vector2 _center, float _radius);
	vbCircle(const vbCircle& circle);
	vbCircle& operator=(const vbCircle& circle);
	virtual ~vbCircle();

	Vector2 center;
	float radius;
};

class vbSingleColourCircle : public vbCircle, public vbSingleColourDrawable
{
public:
	vbSingleColourCircle(Vector2 _center, float _radius, Color _colour);
	vbSingleColourCircle(const vbSingleColourCircle& graphic);
	vbSingleColourCircle& operator=(const vbSingleColourCircle& graphic);
	~vbSingleColourCircle();

	void drawGraphic() override;

};

#endif