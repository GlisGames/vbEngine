#include "vbEngine.h"

// INIT
void vbMessage::init(vbSpriteTexture* _tex, Vector2 _pos, BOOL _isClickDismiss, Vector2 _offset) {
	this->isAlive = TRUE;
	this->position = _pos;
	this->isClickable = TRUE;
	if (_tex == NULL) 
	{
		this->width = 450;
		this->height = 200;
	}
	else
	{
		this->setBackground(_tex);
	}

	this->setCaption("0");
	//this->caption->isDictionaryText = TRUE;
	this->setClickToDismiss(_isClickDismiss);
	this->offset = offset;
}
vbMessage::vbMessage() : vbCanvas(NULL, { 0, 0 }) {
	this->init(NULL, { 0, 0 }, FALSE, offset);
}
vbMessage::vbMessage(vbSpriteTexture* _tex, Vector2 _pos, BOOL _isClickDismiss, Vector2 offset) : vbCanvas(_tex, _pos) {
	this->init(_tex, _pos, _isClickDismiss, offset);
}

// UPDATE
void vbMessage::update() {
	vbCanvas::update();
	if (this->canClickToDismiss && this->isClicked()) {
		this->visible = FALSE;
	}
}
void vbMessage::draw() {
	vbCanvas::draw();
	Rectangle rec = { this->position.x, this->position.y, (FLOAT)this->width, (FLOAT)this->height };
	if (this->background == NULL) {
		DrawRectangleRounded(rec, 0.2f, 0.0f, Fade(BLACK, 0.8f));
	}
	this->caption->draw();
}
// GETTERS & SETTERS
BOOL vbMessage::getClickToDismiss() {
	return this->canClickToDismiss;
}
void vbMessage::setClickToDismiss(BOOL _isClickDismiss) {
	if (_isClickDismiss == NULL) this->canClickToDismiss = FALSE;
	else this->canClickToDismiss = _isClickDismiss;
}
// OTHERS
void vbMessage::pushMessage(vbString _txt, vbString _txtAppend, DWORD _timer, Vector2 _offset) {
	this->resetMessage();

	if (this->background == NULL)
	{
		this->caption->setBoundingBox(this->width, this->height);
	}
	else
	{
		this->caption->setBoundingBox((float)this->background->width, (float)this->background->height);
	}

	this->setCaption(_txt, _txtAppend);
	this->caption->colour = WHITE;
	this->visible = TRUE;
	this->offset = offset;
	this->position.x -= this->offset.x;
	this->position.y -= this->offset.y;

	this->moveToFront();
	if (this->background != NULL)
	{
		this->background->sendToBack();
	}
	this->caption->moveToFront();
	if (_timer)
	{
		this->tweens.addtimer("twtimer", _timer)->setTimeBased(TRUE)
			->endLambdaSet(
				lvoid{
					this->tweens.addtween("twfadeout", (this->background != NULL) ? &this->background->colour.a : &this->backgroundColor.a, 255, 0, 1000, twOneShot)->setTimeBased(TRUE);
					this->tweens.addtween("twfadeouttxt", &this->caption->colour.a, 255, 0, 1000, twOneShot)->setTimeBased(TRUE)
						->endLambdaSet(lvoid{
						this->visible = FALSE;
						});
				});
	}
}
void vbMessage::resetOffset()
{
	this->offset = { 0.0f, 0.0f };
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
