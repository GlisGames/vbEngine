#ifndef VBMESSAGE_H
#define VBMESSAGE_H
#include "vbCanvas.h"

class vbMessage : public vbCanvas {
private:
	BOOL canClickToDismiss = TRUE;
	void init(Texture2D* tex, Vector2 pos, BOOL b);
public:
	Color backgroundColor = WHITE;
	float borderThickness = 5;
	vbMessage();
	vbMessage(Texture2D* tex, Vector2 pos, BOOL b);
	void update();
	void render();
	void resetMessage();
	BOOL getClickToDismiss();
	void setClickToDismiss(BOOL b);
	void pushMessage(vbString txt, vbString txtAppend = "", int timer = 60);
};

#endif
