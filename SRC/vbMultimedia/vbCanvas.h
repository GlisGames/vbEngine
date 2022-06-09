#ifndef VBCANVAS_H
#define VBCANVAS_H

#include "vbContainer.h"
#include "vbTextBox.h"

class vbCanvas : public vbContainer
{
private:
public:
	void init(vbSpriteTexture* tex, Rectangle position, vbString stext = "");
	vbImage* background = NULL;
	vbTextbox* caption = NULL;
	vbCanvas();
	~vbCanvas();
	virtual void setup();
	virtual void update();
	virtual void draw();
	explicit vbCanvas(Rectangle rect, vbString stext = "");
	explicit vbCanvas(vbSpriteTexture* tex, Vector2 position, vbString stext = ""); 
	void setBackground(vbSpriteTexture* tex);
	void setCaption(vbString stext, const char * appendText);
	void setCaption(vbString stext, vbString appendText = "");
	BYTE borderWidth = 0;
	Color borderColor = BLACK;
};

#endif // !VBCANVAS_H