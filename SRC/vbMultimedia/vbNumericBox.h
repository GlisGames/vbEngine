#ifndef VBNUMERICBOX_H
#define VBNUMERICBOX_H
#include "vbButton.h"
#include "vbTextBox.h"
#include <functional>

#define DEFAULT_MIN_REACH_HANDLE [](vbNumericBox* e) \
	{ \
	string val = " " + string(formatMoney(e->min)); \
	pGAME->alertBox->pushMessage("txt_min_reach", val); \
	} \

#define DEFAULT_MAX_REACH_HANDLE [](vbNumericBox* e) \
	{ \
	string val = " " + string(formatMoney(e->max)); \
	pGAME->alertBox->pushMessage("txt_max_reach", val); \
	}

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
	Sound* soundMinus = NULL;
	Sound* soundPlus = NULL;
	std::function<void(vbNumericBox*)> minReachHandle;
	std::function<void(vbNumericBox*)> maxReachHandle;

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

