#ifndef VBMESSAGE_H
#define VBMESSAGE_H
#include "vbCanvas.h"

class vbMessage : public vbCanvas {
private:
	BOOL canClickToDismiss = TRUE;
	void init(Texture2D* tex, Vector2 pos, BOOL b);
	void resetMessage();
public:
	vbMessage();
	vbMessage(Texture2D* tex, Vector2 pos, BOOL b);
	void update();
	void render();
	BOOL getClickToDismiss();
	void setClickToDismiss(BOOL b);
	void pushMessage(vbString txt, int timer=60);
};

#endif
