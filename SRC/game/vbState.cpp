#include "vbEngine.h"

vbState::vbState()
{
	this->exitState = 0xFF;
	this->canvas = new vbCanvas({ 0,0, pGAME->gameResolution.x, pGAME->gameResolution.y });
	this->canvas->visible = FALSE;
	this->canvas->isAlive = FALSE;
	pGAME->mainScene->addObject(this->canvas);
	pGAME->stateList.push_back(this);
}

void vbState::stateExit(WORD s)
{
	this->exitState = s;
}
BOOL vbState::afterAndEvery(DWORD after, DWORD every)
{
	return (this->time > after && !((this->time + after) % every));
}
BOOL vbState::afterAndUntil(DWORD after, DWORD until)
{
	return (this->time > after && (this->time < until));
}
BOOL vbState::afterAndEveryUntil(DWORD after, DWORD until, DWORD every)
{
	return (this->time > after && !((this->time + after) % every) && (this->time < until));
}

BOOL vbState::afterAndEveryFrame(DWORD after, DWORD every)
{
	return (this->frame > after && !((this->frame + after) % every));
}
BOOL vbState::afterAndUntilFrame(DWORD after, DWORD until)
{
	return (this->frame > after && (this->frame < until));
}
BOOL vbState::afterAndEveryUntilFrame(DWORD after, DWORD until, DWORD every)
{
	return (this->frame > after && !((this->frame + after) % every) && (this->frame < until));
}

WORD vbState::run()
{
	if (this->firstIn == TRUE)
	{
		this->exitState = 0xFF;
		this->frame = 0;
		this->time = 0;
		this->init();
		this->firstIn = FALSE;
		this->canvas->isAlive = TRUE;
	}
	this->tweens.stepAll();
	this->checkButton();
	this->update();
	if (this->exitState != 0xFF)
	{
		this->exit();
		this->canvas->isAlive = FALSE;
		this->firstIn = TRUE;
		return this->exitState;
	}
	this->frame++;
	this->time+=getElapsedMillis();
	return 0xFF;
}
