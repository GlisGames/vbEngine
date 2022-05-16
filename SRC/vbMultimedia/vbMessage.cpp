#include "vbEngine.h"

// INIT
void vbMessage::init(Texture2D* tex, Vector2 pos, BOOL b, Vector2 offset) {
	this->isAlive = TRUE;
	this->position = pos;
	this->isClickable = TRUE;
	if (tex == NULL) {
		this->width = 450;
		this->height = 200;
	}
	else
		this->setBackground(tex);
	this->setCaption("0");
	this->caption->isDictionaryText = TRUE;
	this->setClickToDismiss(b);
	this->offset = offset;
}
vbMessage::vbMessage() : vbCanvas(NULL, { 0, 0 }) {
	this->init(NULL, { 0, 0 }, FALSE, offset);
}
vbMessage::vbMessage(Texture2D* tex, Vector2 pos, BOOL b, Vector2 offset) : vbCanvas(tex, pos) {
	this->init(tex, pos, b, offset);
}

// UPDATE
void vbMessage::update() {
	if (this->canClickToDismiss && this->isClicked()) {
		this->visible = FALSE;
	}
}
void vbMessage::render() {
	if (this->background == NULL) {
		DrawRectangleLinesEx({ this->position.x, this->position.y, 450, 200 }, borderThickness, backgroundColor);
	}
}
// GETTERS & SETTERS
BOOL vbMessage::getClickToDismiss() {
	return this->canClickToDismiss;
}
void vbMessage::setClickToDismiss(BOOL b) {
	if (b == NULL) this->canClickToDismiss = FALSE;
	else this->canClickToDismiss = b;
}
// OTHERS
void vbMessage::pushMessage(vbString txt, vbString txtAppend, int timer, int posx, int posy) {
	this->resetMessage();
	this->setCaption(txt, txtAppend);
	this->caption->setBoundingBox((float)this->background->width, (float)this->background->height);
	this->visible = TRUE;
	this->offset = {(float)posx, (float)posy};
	this->position.x -= this->offset.x;
	this->position.y -= this->offset.y;

	this->moveToFront();
	if (timer)
	{
		this->tweens.addtimer("twtimer", timer)
			->endLambdaSet(
				lvoid{
					this->tweens.addtween("twfadeout", (this->background != NULL) ? &this->background->colour.a : &this->backgroundColor.a, 255, 0, 60, twOneShot);
					this->tweens.addtween("twfadeouttxt", &this->caption->colour.a, 255, 0, 60, twOneShot)
						->endLambdaSet(lvoid{
						this->visible = FALSE;
						});
				});
	}
}
void vbMessage::resetOffset()
{
	this->offset = {0.0f, 0.0f};
}
void vbMessage::resetMessage() {
	if (this->background != NULL) this->background->colour.a = 255;
	this->backgroundColor.a = 255;
	this->caption->colour.a = 255;
	this->tweens.clear();
	this->visible = FALSE;
	this->position.x += this->offset.x;
	this->position.y += this->offset.y;
	this->resetOffset();
}
