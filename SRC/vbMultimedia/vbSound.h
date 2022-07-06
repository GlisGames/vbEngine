#ifndef VBSOUND_H
#define VBSOUND_H
#include "basetypes.h"
#include "vbLivingObject.h"

class vbSound : public vbGameObject
{
private:
	Sound sound;
	int repeat = 0;
	DWORD fadein = 0;
	DWORD fadeout = 0;
	QWORD startMillis = 0;
	//vbTween twFades; //todo fading tween
public:
	vbSound(Sound thesound);
	vbSound(vbString soundPath);
	void play(int repeatFor = 1, DWORD _fadein = 0, DWORD _fadeout = 0);
	void pause();
	void stop();
	~vbSound();
	virtual void setup();
	virtual void update();
};

#endif // !vbSound_H