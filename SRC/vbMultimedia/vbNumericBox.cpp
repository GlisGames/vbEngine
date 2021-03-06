#include "vbEngine.h"

void vbNumericBox::setup()
{
	vbCanvas::setup();

}
void vbNumericBox::update()
{
	vbCanvas::update();
	if (this->cmdMinus->isClicked()) {
		if (this->value > this->min) {
			this->value -= this->increment;
			this->setValue(this->value);
			if (this->soundMinus != NULL)
				PlaySound(*this->soundMinus);
		}
		//else pGAME->alertBox->pushMessage("txt_min_reach");
	}
	if (this->cmdPlus->isClicked()) {
		if (this->value < this->max) {
			this->value += this->increment;
			this->setValue(this->value);
			if (this->soundPlus != NULL)
				PlaySound(*this->soundPlus);
		}
		//else pGAME->alertBox->pushMessage("txt_max_reach");
	}

}
void vbNumericBox::draw()
{
	vbCanvas::draw();

}

// INIT
void vbNumericBox::init(Vector2 pos, Rectangle minus, Rectangle text, Rectangle plus, BOOL isMoney) {
	this->isAlive = TRUE;
	this->positioningRule = posRule::POS_CANVAS_RELATIVE;
	this->position = pos;
	this->min = 0;
	this->max = 0xFFFFFFFF;
	//this->increment = 50;
	this->increment = 1;

	// MINUS BUTTON
	this->cmdMinus = new vbButton(hwButton::BUTTON_BETDOWN, minus);
	this->cmdMinus->positioningRule = posRule::POS_CANVAS_RELATIVE;
	this->addObject(this->cmdMinus);
	this->cmdMinus->debugBox = TRUE;

	// VALUE
	this->txtValue = new vbTextbox("", text.x, text.y, WHITE, FALSE, "default20", 0);
	this->txtValue->positioningRule = posRule::POS_CANVAS_RELATIVE;
	this->txtValue->useBoundingBox = TRUE;
	this->txtValue->setBoundingBox(text.width, text.height);
	this->addObject(this->txtValue);
	this->txtValue->debugBox = TRUE;

	// PLUS BUTTON
	this->cmdPlus = new vbButton(hwButton::BUTTON_BETUP, plus);
	this->cmdPlus->positioningRule = posRule::POS_CANVAS_RELATIVE;
	this->addObject(this->cmdPlus);
	this->cmdPlus->debugBox = TRUE;

	this->resize();
	this->isMoneyBox = isMoney;
	if(isMoney)
		this->txtValue->setText(formatMoney(this->value));
	else
		this->txtValue->setText(to_string(this->value));
}
vbNumericBox::vbNumericBox(Vector2 pos) {
	this->init(pos, { 0,0,0,0 }, { 0,0,0,0 }, { 0,0,0,0 });
}
vbNumericBox::vbNumericBox(Vector2 pos, Rectangle minus, Rectangle text, Rectangle plus, BOOL isMoney) {
	this->init(pos, minus, text, plus, isMoney);
}

// GETTERS & SETTERS
DWORD vbNumericBox::getValue() {
	return this->value;
}
DWORD vbNumericBox::getMin() {
	return this->min;
}
DWORD vbNumericBox::getMax() {
	return this->max;
}
DWORD vbNumericBox::getIncrement() {
	return this->increment;
}
void vbNumericBox::setValue(DWORD _value) {
	this->value = _value;
	if(this->isMoneyBox)
		this->txtValue->setText(formatMoney(this->value));
	else
		this->txtValue->setText(to_string(this->value));
}
void vbNumericBox::setMin(DWORD _min) {
	this->min = _min;
}
void vbNumericBox::setMax(DWORD _max) {
	this->max = _max;
}
void vbNumericBox::setIncrement(DWORD _increment) {
	this->increment = _increment;
}
