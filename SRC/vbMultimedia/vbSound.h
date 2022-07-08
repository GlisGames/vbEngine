#ifndef VBSOUND_H
#define VBSOUND_H
#include "basetypes.h"
#include "vbLivingObject.h"

class vbSound : public vbGameObject
{
private:
	DWORD soundID = 0;
public:
	vbSound(vbString soundPath);
	vbSound() {};
	void play(DWORD volume = 100, BOOL loop = FALSE, DWORD fadeinFrames = 0);
	void pause(DWORD fadeFrames = 0);
	void stop(DWORD fadeOutFrames = 0);
	void setVolume(DWORD gain);
	void loadSound(vbString soundPath);
	~vbSound();
	virtual void setup();
	virtual void update();
};

#endif // !vbSound_H