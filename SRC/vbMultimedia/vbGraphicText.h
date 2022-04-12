#ifndef VB_SPRITEFONT
#define VB_SPRITEFONT

#include <string>
#include "vbGraphicObject.h"
#include "raylib.h"
#include "basetypes.h"
/*
class vbSpriteFontChar
{
public:
	vbSpriteFontChar(DWORD _id, WORD x, WORD y, WORD width, WORD height, WORD xoffset, WORD yoffset, WORD xadvance);
	DWORD id = 0;
	WORD x = 0;
	WORD y = 0;
	WORD width = 0;
	WORD height = 0;
	WORD xoffset = 0;
	WORD yoffset = 0;
	WORD xadvance = 0;
};

class vbSpriteFont
{
private:
	Texture2D fontTexture = { 0 };
	WORD lineHeight = 0;
	WORD scaleW = 0;
	WORD scaleH = 0;
	WORD pages = 0;
	vector<vbSpriteFontChar> chars;
public:
	vbSpriteFont(string spriteFile, string jsonFile);
	vbSpriteFont();
	BOOL loadFont(string spriteFile, string jsonFile);
};
*/

class vbGraphicText : public vbGraphicObject
{
private:
	string text = "";
	Font font = { 0 };
public:
	WORD size = 0;
	WORD spacing = 1;
	vbGraphicText();
	vbGraphicText(Font _font, string _initialText = "", Vector2 _position = {0,0}, WORD _size = 1.0f);
	void settext(string _text);
	void setFont(Font _font);
	//virtual void setup();
	virtual void update();
	virtual void draw();
};

#endif