#ifndef VBBUTTON_H
#define VBBUTTON_H

#include "vbContainer.h"
#include "basetypes.h"
#include "vbImage.h"
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
	void init(hwButton bID, vbSpriteTexture* tex, Rectangle rect, Color c = WHITE, vbString stext = "");
	void checkSize();
	BOOL bWasMouseOver = FALSE;

public:
	vbButton();
	~vbButton();
	/* Specify button's size by Rectangle */
	explicit vbButton(hwButton bID, Rectangle rect, Color c = WHITE, vbString stext = "", BOOL defaultEffect = TRUE);
	/* Specify button's size by Sprite Texture */
	explicit vbButton(hwButton bID, vbSpriteTexture* tex, Vector2 position, Color c = WHITE, vbString stext = "", BOOL defaultEffect = TRUE);
	virtual void setup();
	virtual void update();
	virtual void draw();

	hwButton buttonID;
	vbImage* image = NULL;
	vbTextbox* text = NULL;
	void setImage(vbSpriteTexture* tex);
	void setText(vbString stext, vbString appendText = "");
	BYTE borderWidth = 0;
	Color borderColor = BLACK;

	/* Combine EventListener.setcallback and Event.subscribe together
	Can be called anytime during the game to get a better control,
	instead of hard-coding the subscribe() statement within init() */

	void bindOnClick(std::function<void (vbButton*)> f);
	void bindOnMouseOver(std::function<void(vbButton*)> f);
	void bindOnMouseOut(std::function<void(vbButton*)> f);

	/* The hard-coded mouse over logics written before,
	turn off the color by percentage */
	void useDefaultHolderEffect(float percent);

protected:
	vbEventListener<vbButton*> onClickListener;
	vbEvent<vbButton*> onClick;
	vbEventListener<vbButton*> onMouseOverListener;
	vbEvent<vbButton*> onMouseOver;
	vbEventListener<vbButton*> onMouseOutListener;
	vbEvent<vbButton*> onMouseOut;
};

#endif // !VBBUTTON_H