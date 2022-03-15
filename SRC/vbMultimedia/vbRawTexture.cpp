#include "vbRawTexture.h"

vbRawTexture::vbRawTexture(Texture2D _texture)
	:texture(_texture)
{
}

vbRawTexture::vbRawTexture(const vbRawTexture& text)
	:texture(text.texture)
{
}

vbRawTexture& vbRawTexture::operator=(const vbRawTexture& text)
{
	this->texture = text.texture;

	return (*this);
}

vbRawTexture::~vbRawTexture()
{
}

vbDrawableTexture::vbDrawableTexture(Texture2D _texture, Vector2 _position, float _rotation, float _scale, Color _color)
	:vbRawTexture(_texture), vbSingleColourDrawable(_color), vbRotateDrawable(_rotation), vbScaleDrawable(_scale), position(_position)
{

}

vbDrawableTexture::vbDrawableTexture(const vbDrawableTexture& text)
	: vbRawTexture(text), vbSingleColourDrawable(text), vbRotateDrawable(text), vbScaleDrawable(text), position(text.position)
{

}

vbDrawableTexture& vbDrawableTexture::operator=(const vbDrawableTexture& text)
{
	vbRawTexture::operator=(text);
	vbSingleColourDrawable::operator=(text);
	vbRotateDrawable::operator=(text);
	vbScaleDrawable::operator=(text);
	this->position = text.position;

	return (*this);
}

vbDrawableTexture::~vbDrawableTexture()
{
}

void vbDrawableTexture::drawGraphic()
{
	DrawTextureEx(this->texture, this->position, this->rotation, this->scale, this->colour);
}
