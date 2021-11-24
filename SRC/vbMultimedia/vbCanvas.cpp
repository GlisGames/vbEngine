#include "vbEngine.h"

vbCanvas::~vbCanvas()
{

}

void vbCanvas::init(Texture2D* tex, Rectangle position, vbString stext)
{
	this->isAlive = TRUE;
	this->position = { position.x, position.y };
	this->width = position.width;
	this->height = position.height;
	this->setBackground(tex);
	this->setCaption(stext);
	//this->caption->setCacheFlag(TRUE);
	this->isClickable = TRUE;
}

vbCanvas::vbCanvas() : vbContainer(0, 0)
{
	this->init(NULL, { 0,0,0,0 });
}

vbCanvas::vbCanvas(Rectangle rect, vbString stext) : vbContainer(rect.width, rect.height)
{
	this->init(NULL, rect, stext);
}

vbCanvas::vbCanvas(Texture2D* tex, Vector2 position, vbString stext) : vbContainer(tex->width, tex->height)
{
	this->init(tex, { position.x, position.y, (FLOAT)tex->width, (FLOAT)tex->height }, stext);
}

void vbCanvas::setCaption(vbString stext)
{
	if (stext != "" || stext.length() > 0)
	{
		if (this->caption == NULL)
		{
			this->caption = new vbTextbox(stext, 0, 0, WHITE);
			this->caption->positioningRule = posRule::POS_CANVAS_RELATIVE;
			this->caption->useBoundingBox = TRUE;
			this->caption->setBoundingBox(this->width, this->height);
			this->addObject(this->caption);
			this->caption->moveToFront();
			//TODO alignment of the text inside the button (left, centered, right, etc..)
		}
		else
			this->caption->setText(stext);
	}
}

void vbCanvas::setBackground(Texture2D* tex)
{
	if (tex == NULL)
		return;

	if (this->background == NULL)
	{
		this->background = new vbImage(tex);
		this->width = (FLOAT)tex->width;
		this->height = (FLOAT)tex->height;
		this->background->positioningRule = posRule::POS_CANVAS_RELATIVE;
		this->background->regPointRule = transformRegRule::REG_CENTER;
		this->background->position = { 0,0 };
		this->addObject(this->background);
	}
	else
		this->background->setTexture(tex);
}