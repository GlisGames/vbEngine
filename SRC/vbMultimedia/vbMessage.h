#ifndef VBMESSAGE_H
#define VBMESSAGE_H
#include "vbCanvas.h"

class vbMessage : public vbCanvas {
private:
	BOOL canClickToDismiss = TRUE;
	void init(Texture2D* tex, Vector2 pos, BOOL b);
	void resetMessage();
public:
	virtual void vbMessage::setup();
	virtual void vbMessage::update();
	virtual void vbMessage::draw();
	Color backgroundColor = WHITE;
	float borderThickness = 5;
	vbMessage();
	vbMessage(Texture2D* tex, Vector2 pos, BOOL b);
	BOOL getClickToDismiss();
	void setClickToDismiss(BOOL b);
	void pushMessage(vbString txt, int timer=60);
};

#endif
