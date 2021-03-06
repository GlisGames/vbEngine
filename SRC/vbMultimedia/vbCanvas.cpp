#include "vbEngine.h"
#include "vbContainer.h"
#include "vbCanvas.h"

vbCanvas::~vbCanvas()
{

}

void vbCanvas::init(vbSpriteTexture* tex, Rectangle position, vbString stext)
{
	this->isAlive = TRUE;
	this->position = { position.x, position.y };
	this->width = position.width;
	this->height = position.height;
	this->setBackground(tex);
	this->setCaption(stext);
}

vbCanvas::vbCanvas() : vbContainer(0, 0)
{
	this->init(NULL, { 0,0,0,0 });
}

void vbCanvas::setup()
{
	vbContainer::setup();
}

void vbCanvas::update()
{
	vbContainer::update();
}

void vbCanvas::draw()
{
	vbContainer::draw();
}

vbCanvas::vbCanvas(Rectangle rect, vbString stext) : vbContainer(rect.width, rect.height)
{
	this->init(NULL, rect, stext);
}

vbCanvas::vbCanvas(vbSpriteTexture* tex, Vector2 position, vbString stext) : vbContainer((tex)?tex->width:0, (tex)?tex->height:0)
{
	if (tex)
		this->init(tex, { position.x, position.y, (FLOAT)tex->width, (FLOAT)tex->height }, stext);
	else
		this->init(tex, { position.x, position.y, 0, 0 }, stext);
}

void vbCanvas::setCaption(vbString stext, const char* appendText)
{
	this->setCaption(stext, vbString(appendText));
}

void vbCanvas::setCaption(vbString stext, vbString appendText)
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
			this->caption->setText(stext, appendText);
	}
}

void vbCanvas::setBackground(vbSpriteTexture* tex)
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