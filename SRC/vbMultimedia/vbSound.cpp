#include "vbSound.h"


vbSound::vbSound(Sound thesound)
{
	this->sound = thesound;
}

vbSound::vbSound(vbString soundPath)
{
	this->sound = LoadSound(soundPath.c_str());
}

void vbSound::play(int repeatFor, DWORD fadein, DWORD fadeout)
{
	this->repeat = repeatFor;
	PlaySound(this->sound);
	this->enabled = TRUE;
	//this->startMillis = getMillis();
	//TODO FADE
}

void vbSound::pause()
{
	PauseSound(this->sound);
	this->enabled = FALSE;
}

void vbSound::stop()
{
	StopSound(this->sound);
	this->enabled = FALSE;
}

vbSound::~vbSound()
{
	UnloadSound(this->sound);
}

void vbSound::setup()
{

}

void vbSound::update()
{
	if (this->repeat < 0 || this->repeat)
	{
		if (!IsSoundPlaying(this->sound))
		{
			PlaySound(this->sound);
			if (this->repeat) this->repeat--;
		}
	}

	if (this->repeat == 0 && !IsSoundPlaying(this->sound))
		this->enabled = FALSE;

}