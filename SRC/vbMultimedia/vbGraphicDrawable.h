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

#endif