#ifndef VB_ASCII_TEXT_GRAPHIC_H
#define VB_ASCII_TEXT_GRAPHIC_H

#include <string>
#include "raylib.h"
#include "vbGraphicDrawable.h"

class vbASCIITextGraphic
{
public:
	vbASCIITextGraphic(std::string _content, Vector2 _position, int _fontSize);
	vbASCIITextGraphic(const vbASCIITextGraphic& graphic);
	vbASCIITextGraphic& operator=(const vbASCIITextGraphic& graphic);
	virtual ~vbASCIITextGraphic();

	std::string content;
	Vector2 position;
	int fontSize;
};

class vbSingleColourASCIIText
	:public vbASCIITextGraphic, public vbSingleColourDrawable
{
public:
	vbSingleColourASCIIText(std::string _content, Vector2 _position, int _fontSize, Color _colour);
	vbSingleColourASCIIText(const vbSingleColourASCIIText& graphic);
	vbSingleColourASCIIText& operator=(const vbSingleColourASCIIText& graphic);
	virtual ~vbSingleColourASCIIText();

	void drawGraphic() override;
};

#endif