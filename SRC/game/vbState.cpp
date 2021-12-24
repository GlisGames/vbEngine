#include "vbEngine.h"

vbState::vbState()
{
	this->GAME = pGAME;
	this->DATA = pDATA;
	this->exitState = 0xFF;
	this->canvas = new vbCanvas({ 0,0, pGAME->gameResolution.x, pGAME->gameResolution.y });
	this->canvas->visible = FALSE;
	this->GAME->mainGame.addObject(this->canvas);
	this->GAME->alertBox = new vbMessage(NULL, { 0, 0 }, TRUE);
	this->GAME->alertBox->visible = FALSE;
	this->GAME->mainGame.addObject(this->GAME->alertBox, "alertBox");
	this->GAME->stateList.push_back(this);
}

void vbState::stateExit(WORD s)
{
	this->exitState = s;
}
BOOL vbState::afterAndEvery(DWORD after, DWORD every)
{
	return (this->frame > after && !((this->frame + after) % every));
}
BOOL vbState::afterAndUntil(DWORD after, DWORD until)
{
	return (this->frame > after && (this->frame < until));
}
BOOL vbState::afterAndEveryUntil(DWORD after, DWORD until, DWORD every)
{
	return (this->frame > after && !((this->frame + after) % every) && (this->frame < until));
}
WORD vbState::run()
{
	if (this->firstIn == TRUE)
	{
		this->exitState = 0xFF;
		this->frame = 0;
		this->init();
		this->firstIn = FALSE;
	}
	this->tweens.stepAll();
	this->checkButton();
	this->update();
	if (this->exitState != 0xFF)
	{
		this->exit();
		this->firstIn = TRUE;
		return this->exitState;
	}
	this->frame++;
	return 0xFF;
}
