#ifndef VB_RECTANGLE_H
#define VB_RECTANGLE_H

#include "vbGraphicObject.h"

class vbRectangle: public vbGraphicObject
{
public:
	vbRectangle(Rectangle _rect);
	//vbRectangle(float x, float y, float width, float height);
	//vbRectangle(const vbRectangle& rectangle);
	//vbRectangle& operator=(const vbRectangle& rectangle);
	virtual ~vbRectangle();
	virtual void setup();
	virtual void update();
	virtual void draw();
};

#endif