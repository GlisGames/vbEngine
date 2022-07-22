#include "vbEngine.h"
#include <vector>

void vbSequence::setup()
{
	vbImage::setup();

}

void vbSequence::update()
{
	vbImage::update();
	this->stepAnim();
}

void vbSequence::draw()
{
	vbImage::draw();
}

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

vbSequence::vbSequence(vbSpriteTexture2Dvector* slist, Vector2 pos, WORD frameFrequency, std::string name, WORD layer)
{
	this->name = name;
	this->seqList = slist;
	this->position = pos;
	this->actualIndex = 0;
	this->frameCounter = 0;
	this->frameFreq = frameFrequency;
	this->enabled = FALSE;
	this->setLayer(layer);
	this->setTexture(slist->at(actualIndex)); //TODO not found protection
	this->type = TYPE_SEQUENCE;
}

void vbSequence::startAnimByTime(DWORD FPS, seqRepeatType rep)
{
	this->enabled = TRUE;
	this->repeat = rep;
	this->frameFreq = FPS;
}

void vbSequence::startAnimByFrame(seqRepeatType rep, WORD frameFrequency)
{
	this->enabled = TRUE;
	this->repeat = rep;
	this->frameFreq = frameFrequency;
}

void vbSequence::resetAnim()
{
	this->actualIndex = 0;
	this->frameCounter = 0;
	if(this->seqList)
		this->setTexture(this->seqList->at(this->actualIndex));
}

void vbSequence::stopAnim()
{
	this->enabled = FALSE;
	this->resetAnim();
}

bool vbSequence::isFinished()
{
	if (this->actualIndex >= this->seqList->size() - 1)
	{
		return true;
	}
	return false;
}

void vbSequence::stepTo(WORD frame)
{
	if(frame < this->seqList->size())
		this->setTexture(this->seqList->at(frame));
}

void vbSequence::stepAnim()
{
	if (this->enabled == FALSE || this->seqList == NULL || this->frameFreq == 0)
		return;

	SDWORD advance = 0;

	if (!this->isTimeBased)
		this->frameCounter++;

	if (this->isTimeBased && 
		(getMillis() - this->frameCounter >= roundf(1000.0f / this->frameFreq))) //prevent division by zero
	{
		QWORD calc = getMillis() - this->frameCounter;
		WORD fps = roundf(1000.0f / this->frameFreq);
		this->frameCounter = getMillis();
		advance = TRUE;
	}

	if ((!this->isTimeBased && !(this->frameCounter % this->frameFreq)))
		advance = 1;

	if(advance)
	{
		if (this->repeat == seqRepeatType::REP_BEGINTOEND)
		{
			if ((this->actualIndex + advance) >= this->seqList->size())
				this->actualIndex = 0;
			else
				this->actualIndex += advance;
		}
				
		if (this->repeat == seqRepeatType::REP_YOYO)
		{
			if ((this->actualIndex + advance) >= this->seqList->size()) //if we reaced the end
				this->yoyoDirection = 1;
			else if ((this->actualIndex - advance) < 0) //if we are back to the beginning
				this->yoyoDirection = -1 * (advance);
			
			this->actualIndex += this->yoyoDirection;

		}
		else if ((this->repeat == seqRepeatType::REP_ONETIME))
		{
			if ((this->actualIndex + advance) < this->seqList->size())
				this->actualIndex += advance;
			else
				this->actualIndex = this->seqList->size() - 1;
		}
	}

	this->setTexture(this->seqList->at(this->actualIndex));
}

// vbSequenceMap
vbSpriteTexture2Dvector* vbSequenceMap::operator [](std::string str)
{
	std::transform(str.begin(), str.end(), str.begin(), ::toupper);
	vbSpriteTexture2Dvector* ret = this->at(str);
	return ret;
}