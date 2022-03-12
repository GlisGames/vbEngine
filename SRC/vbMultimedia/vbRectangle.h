#ifndef VB_RECTANGLE_H
#define VB_RECTANGLE_H

#include "raylib.h"
#include "vbShape.h"
#include "vbGraphicDrawable.h"

class vbRectangle: public vbShape
{
public:
	vbRectangle(Rectangle _rect);
	vbRectangle(float x, float y, float width, float height);
	vbRectangle(const vbRectangle& rectangle);
	vbRectangle& operator=(const vbRectangle& rectangle);
	virtual ~vbRectangle();

	Rectangle rect = {0.0f, 0.0f, 0.0f, 0.0f};
};

class vbRoundedDrawRectangle
	: public vbRectangle, public vbRoundedDrawable
{
public:
	vbRoundedDrawRectangle(Rectangle _rect, Color _colour, float _roundness, int _segments);
	vbRoundedDrawRectangle(const vbRoundedDrawRectangle& rectangle);
	vbRoundedDrawRectangle& operator=(const vbRoundedDrawRectangle& rectangle);
	virtual ~vbRoundedDrawRectangle();

	void drawGraphic() override;
};

#endif