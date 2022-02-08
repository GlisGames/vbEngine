#ifndef VBBUTTON_H
#define VBBUTTON_H

#include "basetypes.h"
#include "vbContainer.h"
#include "vbImage.h"
#include "vbTextBox.h"

class vbButton : public vbContainer
{
private:
	void init(hwButton bID, Texture2D* tex, Rectangle position, Color c = WHITE, vbString stext = "");
	void checkSize();
public:
	vbButton();
	~vbButton();
	vbImage* image = NULL;
	vbTextbox* text = NULL;
	void setImage(Texture2D* tex);
	explicit vbButton(hwButton bID, Rectangle rect, Color c = WHITE, vbString stext = "");
	explicit vbButton(hwButton bID, Texture2D* tex, Vector2 position, Color c = WHITE, vbString stext = "");
	void setText(vbString stext, vbString appendText = "");
	BYTE borderWidth = 0;
	Color borderColor = BLACK;
	hwButton buttonID;

	void update();
};

#endif // !VBBUTTON_H