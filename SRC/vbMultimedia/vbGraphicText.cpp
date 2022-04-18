#include "vbGraphicText.h"
#include "json11.hpp"
#include "vbErrors.h"


vbGraphicText::vbGraphicText()
{
}

vbGraphicText::vbGraphicText(Font _font, string _initialText, Vector2 _position, WORD _size)
	:font(_font), size(_size)
{
	this->position = _position;
	this->setText(_initialText);
}

void vbGraphicText::setText(string _text)
{
	if (this->text != _text)
	{
		this->text = _text;
		Vector2 size = MeasureTextEx(this->font, this->text.c_str(), this->size * this->scale, this->spacing);
		this->width = size.x;
		this->height = size.y;
	}
}

void vbGraphicText::setFont(Font _font)
{
	this->font = _font;
	Vector2 size = MeasureTextEx(this->font, this->text.c_str(), this->size * this->scale, this->spacing);
	this->width = size.x;
	this->height = size.y;
}

void vbGraphicText::update()
{
	vbGraphicObject::update();
}

void vbGraphicText::draw()
{
	vbGraphicObject::draw();
	Vector2 origin = { 0,0 };
	if (this->transformed.rotation != 0)
	{	// here we change the point of origin so that the rotation point is centered, look inside 'DrawTexturePro' to know why
		origin = { ((float)this->transformed.width / 2.0f), ((float)this->transformed.height / 2.0f) };
		this->transformed.position.x += origin.x;
		this->transformed.position.y += origin.y;
	}
	DrawTextPro(this->font, this->text.c_str(), this->transformed.position, origin, this->transformed.rotation, this->size*this->transformed.scale, this->spacing, this->transformed.colour);
}


/*
vbSpriteFont::vbSpriteFont(string spriteFile, string jsonFile)
{
	this->loadFont(spriteFile, jsonFile);
}

vbSpriteFont::vbSpriteFont()
{
}

BOOL vbSpriteFont::loadFont(string _spriteFile, string _jsonFile)
{
	nlohmann::json rec;
	Texture2D fontTex = LoadTexture(_spriteFile.c_str());
	if (fontTex.width = 0)
		PANIC(TextFormat("FONT SPRITE FILE %s NOT FOUND", _spriteFile.c_str()));

	char* jsonfile = LoadFileText(_jsonFile.c_str());
	try
	{
		rec = nlohmann::json::parse(jsonfile);
	}
	catch (nlohmann::json::parse_error& e)
	{
		PANIC(e.what());
		return FALSE;
	}
	UnloadFileText(jsonfile);

	if (rec.contains("lineHeight") && rec.contains("scaleW")&& rec.contains("scaleH")&& rec.contains("pages")&& rec.contains("chars"))
	{
		this->lineHeight = rec["lineHeight"];
		this->scaleH = rec["scaleH"];
		this->scaleW = rec["scaleW"];
		this->pages = rec["pages"];
		for (const auto& element : rec["chars"])
		{
			this->chars.push_back(
				vbSpriteFontChar(
					element["id"], 
					element["x"], 
					element["y"], 
					element["width"], 
					element["height"], 
					element["xoffset"], 
					element["yoffset"], 
					element["xadvance"]
				)
			);
		}
	}
	else
	{
		PANIC("FONT JSON FILE FORMAT ERROR");
		return FALSE;
	}

	return TRUE;
}

vbSpriteFontChar::vbSpriteFontChar(DWORD _id, WORD _x, WORD _y, WORD _width, WORD _height, WORD _xoffset, WORD _yoffset, WORD _xadvance)
	:id(_id), x(_x), y(_y), width(_width), height(_height), xoffset(_xoffset), yoffset(_yoffset), xadvance(_xadvance)
{
}

*/