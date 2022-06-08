#ifndef VBMESSAGE_H
#define VBMESSAGE_H
#include "vbCanvas.h"

class vbMessage : public vbCanvas {
private:
	BOOL canClickToDismiss = TRUE;
	void init(vbSpriteTexture* _tex, Vector2 _pos, BOOL _isClickDismiss, Vector2 _offset);
	Vector2 offset = { 0.0f, 0.0f };
public:
	Color backgroundColor = WHITE;
	vbMessage();
	vbMessage(vbSpriteTexture* _tex, Vector2 _pos = { 0,0 }, BOOL _isClickDismiss = TRUE, Vector2 _offset = { 0, 0 });
	void update();
	void draw();
	void resetMessage();
	BOOL getClickToDismiss();
	void setClickToDismiss(BOOL b);
	void pushMessage(vbString _txt, vbString _txtAppend = "", DWORD _timer = 60, Vector2 _offset = { 0,0 });
	void resetOffset();
};

#endif
