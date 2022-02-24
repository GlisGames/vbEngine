#ifndef VBMESSAGE_H
#define VBMESSAGE_H
#include "vbCanvas.h"

class vbMessage : public vbCanvas {
private:
	BOOL canClickToDismiss = TRUE;
	void init(vbSpriteTexture* tex, Vector2 pos, BOOL b);
	void resetMessage();
public:
	virtual void vbMessage::setup();
	virtual void vbMessage::update();
	virtual void vbMessage::draw();
	Color backgroundColor = WHITE;
	float borderThickness = 5;
	vbMessage();
	vbMessage(vbSpriteTexture* tex, Vector2 pos, BOOL b);
	BOOL getClickToDismiss();
	void setClickToDismiss(BOOL b);
	void pushMessage(vbString txt, int timer=60);
};

#endif
