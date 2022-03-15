#include "vbEngine.h"
#include "vbContainer.h"


vbButton::~vbButton()
{

}

void vbButton::setup()
{
	vbContainer::setup();
}

void vbButton::update()
{
	vbContainer::update();
	if (this->image != NULL)
	{
		if (this->isMouseOver() &&
			(this->image->colour.r == this->image->fallbackColour.r) &&
			(this->image->colour.g == this->image->fallbackColour.g) &&
			(this->image->colour.b == this->image->fallbackColour.b))
		{
			this->image->colour = ColorTurnOffPercent(this->image->colour, 70.0f);
		}
		else if (!this->isMouseOver())
		{
			this->image->colour = this->image->fallbackColour;
		}
	}
	if (this->isClicked())
		this->onClick.trigger(this);
}

void vbButton::draw()
{
	vbContainer::draw();

}

void vbButton::checkSize()
{
	Vector2 dim = { (float)this->width,(float)this->height };
	if (this->text != NULL)
	{

	}
}

void vbButton::init(hwButton bID, vbSpriteTexture* tex, Rectangle position, Color c, vbString stext)
{
	this->isAlive = TRUE;
	this->position = { position.x, position.y };
	this->width = position.width;
	this->height = position.height;
	this->setImage(tex);
	this->setText(stext);
	if (this->image != NULL)
	{
		this->image->fallbackColour = c;
		this->image->colour = this->image->fallbackColour;
	}
	this->isClickable = TRUE;
	this->buttonID = bID;
	this->onClick.subscribe(&this->onClickListener);
}

vbButton::vbButton() : vbContainer(0, 0)
{
	this->init(hwButton::BUTTON_NONE, NULL, { 0,0,0,0 });
}

vbButton::vbButton(hwButton bID, vbSpriteTexture* tex, Vector2 position, Color c, vbString stext)
	:vbContainer(tex->width, tex->height)
{
	this->init(bID, tex, { position.x, position.y, (FLOAT)tex->width, (FLOAT)tex->height }, c, stext);
}

vbButton::vbButton(hwButton bID, Rectangle rect, Color c, vbString stext)
	:vbContainer(rect.width, rect.height)
{
	this->init(bID, NULL, rect, c, stext);
}

void vbButton::setText(vbString stext, vbString appendText)
{
	if (stext != "" || stext.length() > 0)
	{
		if (this->text == NULL)
		{
			this->text = new vbTextbox(stext, 0, 0, WHITE);
			this->text->positioningRule = posRule::POS_CANVAS_RELATIVE;
			this->text->useBoundingBox = TRUE;
			this->text->setBoundingBox(this->width, this->height);
			this->addObject(this->text);
			this->text->moveToFront();
			//TODO alignment of the text inside the button (left, centered, right, etc..)
		}
		else
			this->text->setText(stext, appendText);
	}
}

void vbButton::setImage(vbSpriteTexture* tex)
{
	if (tex == NULL)
		return;

	if (this->image == NULL)
	{
		this->image = new vbImage(tex);
		this->width = (FLOAT)tex->width;
		this->height = (FLOAT)tex->height;
		this->image->positioningRule = posRule::POS_CANVAS_RELATIVE;
		this->image->regPointRule = transformRegRule::REG_CENTER;
		this->image->position = { 0,0 };
		this->addObject(this->image);
	}
	else
		this->image->setTexture(tex);
}