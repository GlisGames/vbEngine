#ifndef VB_RAW_TEXTURE_H
#define VB_RAW_TEXTURE_H

#include "raylib.h"
#include "vbGraphicDrawable.h"

class vbRawTexture
{
public:
	vbRawTexture(Texture2D _texture);
	vbRawTexture(const vbRawTexture& text);
	vbRawTexture& operator=(const vbRawTexture& text);
	virtual ~vbRawTexture();

	Texture2D texture;
};

class vbDrawableTexture
	:public vbRawTexture, public vbRotateDrawable, public vbScaleDrawable, public vbSingleColourDrawable
{
public:
	vbDrawableTexture(Texture2D _texture, Vector2 _position, float _rotation = 0.0f, float _scale = 1.0f, Color _color = WHITE);
	vbDrawableTexture(const vbDrawableTexture& text);
	vbDrawableTexture& operator=(const vbDrawableTexture& text);
	virtual ~vbDrawableTexture();

	//Why is it still virtual? Because you can create it for draw part of texture
	virtual void drawGraphic();

	Vector2 position;
};

#endif