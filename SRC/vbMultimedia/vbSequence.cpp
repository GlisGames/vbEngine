#include "vbEngine.h"
#include "vbSequence.h"
#include <vector>

vbSequence::vbSequence()
{
	this->seqList = {0};
	this->position = {0,0};
	this->actualIndex = 0;
	this->frameCounter = 0;
	this->frameFreq = 1;
	this->enabled = TRUE;
	this->setLayer(0);
	this->texture = NULL;
	this->type = TYPE_SEQUENCE;
	this->name = "";
}

vbSequence::vbSequence(Texture2Dvector slist, Vector2 pos, std::string name, WORD layer, WORD frameFrequency)
{
	this->name = name;
	this->seqList = slist;
	this->position = pos;
	this->actualIndex = 0;
	this->frameCounter = 0;
	this->frameFreq = frameFrequency;
	this->enabled = TRUE;
	this->setLayer(layer);
	this->setTexture(slist[actualIndex]);
	this->type = TYPE_SEQUENCE;
}

void vbSequence::startAnim(seqRepeatType rep, WORD frameFrequency)
{
	this->enabled = TRUE;
	this->repeat = rep;
	this->frameFreq = frameFrequency;
}

void vbSequence::resetAnim()
{
	this->actualIndex = 0;
	this->frameCounter = 0;
}

void vbSequence::stopAnim()
{
	this->enabled = FALSE;
	this->resetAnim();
}
bool vbSequence::isFinshed()
{
	if (this->actualIndex >= this->seqList.size() - 1)
	{
		return true;
	}
	return false;
}

void vbSequence::stepAnim()
{
	if (this->enabled == FALSE)
		return;

	if(this->frameCounter >= 0xFFFFFFFF)
		this->frameCounter=0;
	else
		this->frameCounter++;

	if (!(this->frameCounter % this->frameFreq))
	{
		if (this->repeat == seqRepeatType::REP_BEGINTOEND)
		{
			if ((this->actualIndex + 1) >= this->seqList.size())
				this->actualIndex = 0;
			else
				this->actualIndex++;
		}
				
		if (this->repeat == seqRepeatType::REP_YOYO)
		{
			if ((this->actualIndex + 1) >= this->seqList.size()) //se siamo arrivat in fondo
				this->yoyoDirection = 1;
			else if ((this->actualIndex - 1) < 0) //se siamo tornati a capo
				this->yoyoDirection = -1;
			
			this->actualIndex += this->yoyoDirection;

		}
		else if ((this->repeat == seqRepeatType::REP_ONETIME)&&((this->actualIndex + 1) < this->seqList.size()))
			this->actualIndex++;
	}

	this->setTexture(this->seqList[this->actualIndex]);
}