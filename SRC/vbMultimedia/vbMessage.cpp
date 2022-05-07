#include "vbEngine.h"

// INIT
void vbMessage::init(Texture2D* tex, Vector2 pos, BOOL b) {
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
}
vbMessage::vbMessage() : vbCanvas(NULL, { 0, 0 }) {
	this->init(NULL, { 0, 0 }, FALSE);
}
vbMessage::vbMessage(Texture2D* tex, Vector2 pos, BOOL b) : vbCanvas(tex, pos) {
	this->init(tex, pos, b);
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
void vbMessage::pushMessage(vbString txt, vbString txtAppend, int timer) {
	this->resetMessage();
	this->setCaption(txt, txtAppend);
	this->caption->setBoundingBox((float)this->background->width, (float)this->background->height);
	this->visible = TRUE;
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
void vbMessage::resetMessage() {
	if (this->background != NULL) this->background->colour.a = 255;
	this->backgroundColor.a = 255;
	this->caption->colour.a = 255;
	this->tweens.clear();
	this->visible = FALSE;
}
