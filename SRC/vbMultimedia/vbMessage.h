#ifndef VBMESSAGE_H
#define VBMESSAGE_H
#include "vbCanvas.h"

class vbMessage : public vbCanvas {
private:
	int timer = 0;
	BOOL canClickToDismiss = FALSE;
	void init(Texture2D* tex, Vector2 pos, int timer, BOOL b);
public:
	vbMessage();
	vbMessage(Texture2D* tex, Vector2 pos, int timer, BOOL b);
	void update();
	void render();
	int getTimer();
	BOOL getClickToDismiss();
	void setTimer(int timer);
	void setClickToDismiss(BOOL b);
	void toggleClickToDismiss();
	void clickToDismiss();
};

#endif
