#ifndef VB_GRAPHIC_DRAWABLE_H
#define VB_GRAPHIC_DRAWABLE_H

#include "raylib.h"

class vbGraphicDrawable
{
public:
	vbGraphicDrawable();
	vbGraphicDrawable(const vbGraphicDrawable& graphic);
	vbGraphicDrawable& operator=(const vbGraphicDrawable& graphic);
	virtual ~vbGraphicDrawable();

	//why not draw(), because when we make the graphic object, it also have draw() 
	virtual void drawGraphic() = 0;
};

class vbSingleColourDrawable:
	public vbGraphicDrawable
{
public:
	vbSingleColourDrawable(Color _colour);
	vbSingleColourDrawable(const vbSingleColourDrawable& graphic);
	vbSingleColourDrawable& operator=(const vbSingleColourDrawable& graphic);
	virtual ~vbSingleColourDrawable();

	virtual void drawGraphic() = 0;

	Color colour;
};

class vbRoundedDrawable
	:public vbSingleColourDrawable
{
public:
	vbRoundedDrawable(Color _colour, float _roundness, int _segments);
	vbRoundedDrawable(const vbRoundedDrawable& graphic);
	vbRoundedDrawable& operator=(const vbRoundedDrawable& graphic);
	virtual ~vbRoundedDrawable();

	virtual void drawGraphic() = 0;

	float roundness;
	int segments;
};

class vbScaleDrawable
	:public vbGraphicDrawable
{
public:
	vbScaleDrawable(float _scale = 1.0f);
	vbScaleDrawable(const vbScaleDrawable& graphic);
	vbScaleDrawable& operator=(const vbScaleDrawable& graphic);
	virtual ~vbScaleDrawable();

	virtual void drawGraphic() = 0;

	float scale;
};

class vbRotateDrawable
	:public vbGraphicDrawable
{
public:
	vbRotateDrawable(float _rotation = 0.0f);
	vbRotateDrawable(const vbRotateDrawable& graphic);
	vbRotateDrawable& operator=(const vbRotateDrawable& graphic);
	virtual ~vbRotateDrawable();

	virtual void drawGraphic() = 0;

	float rotation;
};
#endif