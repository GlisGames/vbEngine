#include "vbEngine.h"

// INIT
void vbMessage::init(Texture2D* tex, Vector2 pos, int timer, BOOL b) {
	this->isAlive = TRUE;
	this->position = pos;
	this->width = tex->width;
	this->height = tex->height;
	this->isClickable = TRUE;
	this->setTimer(timer); // Number of frames;
	this->setClickToDismiss(b);
}
vbMessage::vbMessage() : vbCanvas(NULL, { 0, 0 }) {
	this->init(NULL, { 0, 0 }, NULL, FALSE);
}
vbMessage::vbMessage(Texture2D* tex, Vector2 pos, int timer, BOOL b) : vbCanvas(tex, pos) {
	this->init(tex, pos, timer, b);
}

// UPDATE
void vbMessage::update() {
	if (timer > 0) timer--;
	if (timer == 0) this->isAlive = FALSE;
}
void vbMessage::render() {
	// RENDER BORDER HERE
	DrawRectangleLines(this->position.x, this->position.y, this->width, this->height, RED);
}
// GETTERS & SETTERS
int vbMessage::getTimer() {
	return this->timer;
}
BOOL vbMessage::getClickToDismiss() {
	return this->canClickToDismiss;
}
void vbMessage::setTimer(int timer) {
	if (timer == NULL) this->timer = 120;
	else this->timer = timer;
}
void vbMessage::setClickToDismiss(BOOL b) {
	if (b == NULL) this->canClickToDismiss = FALSE;
	else this->canClickToDismiss = b;
}
void vbMessage::toggleClickToDismiss() {
	this->canClickToDismiss = !this->canClickToDismiss;
}
// OTHERS
void vbMessage::clickToDismiss() {
	if (this->canClickToDismiss && IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && this->isMouseOver()) {
		this->isAlive = FALSE;
	}
}