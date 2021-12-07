#include "vbEngine.h"
// INIT
void NumericBox::init(Vector2 pos, Rectangle minus, Rectangle text, Rectangle plus) {
	this->isAlive = TRUE;
	this->positioningRule = posRule::POS_CANVAS_RELATIVE;
	this->position = pos;
	this->min = 0;
	this->max = 0xFFFFFFFF;
	this->increment = 50;

	// MINUS BUTTON
	this->cmdMinus = new vbButton(hwButton::BUTTON_BETDOWN, minus);
	this->cmdMinus->positioningRule = posRule::POS_CANVAS_RELATIVE;
	this->addObject(this->cmdMinus);
	//this->cmdMinus->debugBox = TRUE;

	// VALUE
	this->txtValue = new vbTextbox("", text.x, text.y, WHITE, FALSE, "default20", 0);
	this->txtValue->positioningRule = posRule::POS_CANVAS_RELATIVE;
	this->txtValue->useBoundingBox = TRUE;
	this->txtValue->setBoundingBox(text.width, text.height);
	this->addObject(this->txtValue);
	//this->txtValue->debugBox = TRUE;

	// PLUS BUTTON
	this->cmdPlus = new vbButton(hwButton::BUTTON_BETUP, plus);
	this->cmdPlus->positioningRule = posRule::POS_CANVAS_RELATIVE;
	this->addObject(this->cmdPlus);
	//this->cmdPlus->debugBox = TRUE;

	this->resize();
}
NumericBox::NumericBox(Vector2 pos) {
	this->init(pos, { 0,0,0,0 }, { 0,0,0,0 }, { 0,0,0,0 });
}
NumericBox::NumericBox(Vector2 pos, Rectangle minus, Rectangle text, Rectangle plus) {
	this->init(pos, minus, text, plus);
}
// UPDATE
void NumericBox::update() {
	if (this->cmdMinus->isClicked()) {
		if (this->value > this->min) {
			this->value -= this->increment;
			PlaySound(soundMinus);
		}
		//else pGAME->GUI->alert->pushMessage("txt_min_reach");
	}
	if (this->cmdPlus->isClicked() ) {
		if (this->value < this->max) {
			this->value += this->increment;
			PlaySound(soundPlus);
		}
		//else pGAME->GUI->alert->pushMessage("txt_max_reach");
	}

}
// GETTERS & SETTERS
DWORD NumericBox::getValue() {
	return this->value;
}
DWORD NumericBox::getMin() {
	return this->min;
}
DWORD NumericBox::getMax() {
	return this->max;
}
DWORD NumericBox::getIncrement() {
	return this->increment;
}
void NumericBox::setValue(DWORD _value) {
	this->value = _value;
	//TODO: this->txtValue->setText("");
}
void NumericBox::setMin(DWORD _min) {
	this->min = _min;
}
void NumericBox::setMax(DWORD _max) {
	this->max = _max;
}
void NumericBox::setIncrement(DWORD _increment) {
	this->increment = _increment;
}
