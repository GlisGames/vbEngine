#pragma once
#include "basetypes.h"
#include "vbContainer.h"
#include "vbImage.h"
#include "vbTextBox.h"
#include <vector>

class vbCanvas : public vbContainer
{
private:
public:
	void init(Texture2D* tex, Rectangle position, vbString stext = "");
	vbImage* background = NULL;
	vbTextbox* caption = NULL;
	vbCanvas();
	explicit vbCanvas(Rectangle rect, vbString stext = "");
	explicit vbCanvas(Texture2D* tex, Vector2 position, vbString stext = ""); 
	void setBackground(Texture2D* tex);
	void setCaption(vbString stext);
	BYTE borderWidth = 0;
	Color borderColor = BLACK;
	~vbCanvas();
};