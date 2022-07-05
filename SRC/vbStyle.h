#ifndef VBSTYLES_H
#define VBSTYLES_H
#include "basetypes.h"
#include "vbErrors.h"
#include "vbContainer.h"
#include "json.h"
#include "vector"
#include <string>

Image LoadImageRawFromBuffer(unsigned char* fileData, unsigned int dataSize, int width, int height, int format, int headerSize);

class styleElement
{
public:
	Vector2* position;
	Vector2* size;
	vbSpriteTexture* texture = NULL;
	vbString fontName = "";
	FLOAT scale;
};

class vbStyle : public map <vbString, styleElement>
{
public:
	styleElement operator [](vbString str);
	styleElement* checkName(vbString str);
};

class vbStyleMap : public map <vbString, vbStyle>
{
public:
	vbStyle operator [](vbString str);
	vbStyle* checkName(vbString str);
	BYTE loadStyle(vbString stylename, vbString filename);
};

#endif