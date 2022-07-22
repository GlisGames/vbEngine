#include "vbEngine.h"
#include <vector>

vbSequence::vbSequence()
{
	this->seqList = { 0 };
	this->position = { 0,0 };
	this->actualIndex = 0;
	this->frameCounter = 0;
	this->frameFreq = 1;
	this->enabled = FALSE;
	this->setLayer(0);
	this->texture = NULL;
	this->type = TYPE_SEQUENCE;
	this->name = "";
}

vbSequence::vbSequence(vbSpriteTexture2Dvector* slist, Vector2 pos, std::string name, WORD layer)
{
	this->name = name;
	this->seqList = slist;
	this->position = pos;
	this->actualIndex = 0;
	this->frameCounter = 0;
	this->frameFreq = 1;
	this->enabled = FALSE;
	this->setLayer(layer);
	this->setTexture(slist->at(actualIndex)); //TODO not found protection
	this->type = TYPE_SEQUENCE;
}

void vbSequence::setup()
{
	vbImage::setup();
}

void vbSequence::update()
{
	vbImage::update();
	if (this->seqList != NULL && this->enabled == TRUE)
	{
		if (this->isTimeBased == FALSE)
		{
			this->stepAnimByFrame();
		}
		this->setTexture(this->seqList->at(this->actualIndex));
	}
}

void vbSequence::draw()
{
	vbImage::draw();
}

void vbSequence::startAnimByFrame(WORD frameFrequency, seqRepeatType rep)
{
	this->enabled = TRUE;
	this->repeat = rep;
	this->frameFreq = frameFrequency;
	this->isTimeBased = FALSE;
}

void vbSequence::stepAnimByFrame()
{
	if (this->frameFreq == 0)
		return;

	this->frameCounter++;
	SDWORD advance = 0;

	if ((this->frameCounter % this->frameFreq) == 0)
		advance = 1;

	if (advance > 0)
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

	if (this->actualIndex == this->getTotalFrames() - 1)
	{
		this->syncCallback();
	}
}

void vbSequence::startAnimByTime(DWORD duration, seqRepeatType rep)
{
	this->enabled = TRUE;
	this->repeat = rep;
	this->isTimeBased = TRUE;
	// If already exist, erase the tween and construct again
	this->tweens.killTween("anim");
	this->tweens.addtween("anim", &this->actualIndex, 0, this->getTotalFrames() - 1, duration, tweenRepeat::twRepeat)
		->endLambdaSet(this->syncCallback);
}

void vbSequence::resetAnim()
{
	if (this->isTimeBased == TRUE)
	{
		if (this->enabled == TRUE)
		{
			// Anim has not stopped yet, restart the tween
			this->tweens["anim"].Restart();
		}
		else
		{
			this->tweens["anim"].Stop();
		}
	}
	else
	{
		this->frameCounter = 0;
	}

	this->actualIndex = 0;
	if (this->seqList)
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

// vbSequenceMap
vbSpriteTexture2Dvector* vbSequenceMap::operator [](std::string str)
{
	std::transform(str.begin(), str.end(), str.begin(), ::toupper);
	vbSpriteTexture2Dvector* ret = this->at(str);
	return ret;
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

	if (advance)
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
