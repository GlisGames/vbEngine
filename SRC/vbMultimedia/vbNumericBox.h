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
	vbButton* cmdMinus = NULL;
	vbTextbox* txtValue = NULL;
	vbButton* cmdPlus = NULL;
	Sound soundMinus;
	Sound soundPlus;
	vbNumericBox(Vector2 pos);
	vbNumericBox(Vector2 pos, Rectangle minus, Rectangle text, Rectangle plus);
	void update();
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

