#ifndef VBMESSAGE_H
#define VBMESSAGE_H
#include "vbCanvas.h"

class vbMessage : public vbCanvas {
private:
	BOOL canClickToDismiss = TRUE;
	void init(Texture2D* tex, Vector2 pos, BOOL b, Vector2 offset);
	Vector2 offset = { 0.0f, 0.0f };
public:
	Color backgroundColor = WHITE;
	float borderThickness = 5;
	vbMessage();
	vbMessage(Texture2D* tex, Vector2 pos, BOOL b, Vector2 offset = {0.0f, 0.0f});
	void update();
	void render();
	void resetMessage();
	BOOL getClickToDismiss();
	void setClickToDismiss(BOOL b);
	void pushMessage(vbString txt, vbString txtAppend = "", int timer = 60, int posx = 0, int posy = 0);
	void resetOffset();
};

#endif
