#include "vbSound.h"
#include "vbAudio.h"

vbSound::vbSound(vbString soundPath)
{
	this->loadSound(soundPath);
}

void vbSound::play(DWORD volume, BOOL loop, DWORD fadeinFrames)
{
	if (fadeinFrames)
		vbPlaySoundFade(this->soundID, loop, volume, fadeinFrames);
	else
		vbPlaySound(this->soundID, loop);

	this->enabled = TRUE;
}

void vbSound::pause(DWORD fadeFrames)
{
	vbPauseSound(this->soundID, 1, fadeFrames);
	this->enabled = FALSE;
}

void vbSound::stop(DWORD fadeOutFrames)
{
	if (fadeOutFrames)
		vbStopSoundFade(this->soundID, fadeOutFrames);
	else
		vbStopSound(this->soundID);

	this->enabled = FALSE;
}

void vbSound::setVolume(DWORD gain)
{
	vbSetSoundVolume(this->soundID, gain);
}

vbSound::~vbSound()
{
	vbKillSound(this->soundID);
}
void vbSound::loadSound(vbString soundPath)
{
	int ret = vbLoadSound(soundPath);
	if (ret != -1)
		this->soundID = ret;
}

void vbSound::setup()
{

}

void vbSound::update()
{

}