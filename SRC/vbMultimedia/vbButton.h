#ifndef VBBUTTON_H
#define VBBUTTON_H

#include "vbContainer.h"
#include "vbTextBox.h"
#include "vbEvent.h"

#define lbutton [=](vbButton* b)

class clickHandler
{
private:
	std::list<vbGraphicObject*> items;
public:
	void subscribe(vbGraphicObject* toAdd)
	{
		items.push_back(toAdd);
	}

	void pollClicks()
	{
		if (!IsMouseButtonPressed(0)) //if there's no click don't bother checking
			return;

		for (vbGraphicObject* o : items)
		{

		}
	}
};

class vbButton : public vbContainer
{
private:
	void init(hwButton bID, vbSpriteTexture* tex, Rectangle position, Color c = WHITE, vbString stext = "");
	void checkSize();
public:
	vbButton();
	~vbButton();
	virtual void setup();
	virtual void update();
	virtual void draw();
	vbImage* image = NULL;
	vbTextbox* text = NULL;
	void setImage(vbSpriteTexture* tex);
	explicit vbButton(hwButton bID, Rectangle rect, Color c = WHITE, vbString stext = "");
	explicit vbButton(hwButton bID, vbSpriteTexture* tex, Vector2 position, Color c = WHITE, vbString stext = "");
	void setText(vbString stext, vbString appendText = "");
	BYTE borderWidth = 0;
	Color borderColor = BLACK;
	vbEventListener<vbButton*> onClickListener;
	hwButton buttonID;
	vbEvent<vbButton*> onClick;
};

#endif // !VBBUTTON_H