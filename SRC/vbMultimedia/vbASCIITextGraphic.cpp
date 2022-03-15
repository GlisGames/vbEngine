#include "vbASCIITextGraphic.h"

vbASCIITextGraphic::vbASCIITextGraphic(std::string _content, Vector2 _position, int _fontSize)
	:content(_content), position(_position), fontSize(_fontSize)
{
}

vbASCIITextGraphic::vbASCIITextGraphic(const vbASCIITextGraphic& graphic)
	:content(graphic.content), position(graphic.position), fontSize(graphic.fontSize)
{
}

vbASCIITextGraphic& vbASCIITextGraphic::operator=(const vbASCIITextGraphic& graphic)
{
	this->content = graphic.content;
	this->position = graphic.position;
	this->fontSize = graphic.fontSize;

	return (*this);
}

vbASCIITextGraphic::~vbASCIITextGraphic()
{
}

vbSingleColourASCIIText::vbSingleColourASCIIText(std::string _content, Vector2 _position, int _fontSize, Color _colour)
	:vbASCIITextGraphic(_content, _position, _fontSize), vbSingleColourDrawable(_colour)
{
}

vbSingleColourASCIIText::vbSingleColourASCIIText(const vbSingleColourASCIIText& graphic)
	:vbASCIITextGraphic(graphic), vbSingleColourDrawable(graphic)
{
}

vbSingleColourASCIIText& vbSingleColourASCIIText::operator=(const vbSingleColourASCIIText& graphic)
{
	vbASCIITextGraphic::operator=(graphic);
	vbSingleColourDrawable::operator=(graphic);

	return (*this);
}

vbSingleColourASCIIText::~vbSingleColourASCIIText()
{
}

void vbSingleColourASCIIText::drawGraphic()
{
	DrawText(this->content.c_str(), this->position.x, this->position.y, this->fontSize, this->colour);
}
