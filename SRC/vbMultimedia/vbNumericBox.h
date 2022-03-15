#ifndef VBNUMERICBOX_H
#define VBNUMERICBOX_H
#include "vbButton.h"
#include "vbTextBox.h"

class vbNumericBox : public vbCanvas {
private:
	DWORD value = 0;
	DWORD min = 0;
	DWORD max = 0xFFFFFFFF;
	DWORD increment = 50;
	void init(Vector2 pos, Rectangle minus, Rectangle text, Rectangle plus);
public:
	virtual void setup();
	virtual void update();
	virtual void draw();

	vbButton* cmdMinus = NULL;
	vbTextbox* txtValue = NULL;
	vbButton* cmdPlus = NULL;
	Sound* soundMinus = NULL;
	Sound* soundPlus = NULL;
	vbNumericBox(Vector2 pos);
	vbNumericBox(Vector2 pos, Rectangle minus, Rectangle text, Rectangle plus);
	DWORD getValue();
	DWORD getMin();
	DWORD getMax();
	DWORD getIncrement();
	void setValue(DWORD value);
	void setMin(DWORD min);
	void setMax(DWORD max);
	void setIncrement(DWORD max);
};
#endif 

