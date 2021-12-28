#ifndef VBCANVAS_H
#define VBCANVAS_H

#include "basetypes.h"
#include "vbContainer.h"
#include "vbImage.h"
#include "vbTextBox.h"

class vbCanvas : public vbContainer
{
private:
public:
	void init(Texture2D* tex, Rectangle position, vbString stext = "");
	vbImage* background = NULL;
	vbTextbox* caption = NULL;
	vbCanvas();
	~vbCanvas();
	explicit vbCanvas(Rectangle rect, vbString stext = "");
	explicit vbCanvas(Texture2D* tex, Vector2 position, vbString stext = ""); 
	void setBackground(Texture2D* tex);
	void setCaption(vbString stext, const char * appendText);
	void setCaption(vbString stext, vbString appendText = "");
	BYTE borderWidth = 0;
	Color borderColor = BLACK;
};

#endif // !VBCANVAS_H