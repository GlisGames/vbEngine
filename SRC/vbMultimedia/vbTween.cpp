#include "vbEngine.h"
vbTween::vbTween()
{}

vbTween::~vbTween()
{
	if (this->callbackKill)
		this->callbackKill;
}

void vbTween::init(FLOAT Start_p, FLOAT Stop_p, DWORD TOTsteps, tweenRepeat loop, EasingFunction easingFunction, int repeatFor, tween_callback callback, tween_callback callbackKill)
{
	this->startP = Start_p;
	this->stopP = Stop_p;
	this->totStep = TOTsteps;
	this->repeat = loop;
	this->easingF = easingFunction;
	this->currStep = 0;
	this->repeatFor = repeatFor;
	this->repeatSet = repeatFor;
	this->callbackEnd = callback;
	this->callbackKill = callbackKill;
}
FLOAT vbTween::doTween(FLOAT Start_p, FLOAT Stop_p, WORD currentStep, WORD TOTsteps)
{
	if (currentStep >= TOTsteps)
		currentStep = TOTsteps;
	return (Stop_p - Start_p) * ((FLOAT)currentStep / (FLOAT)TOTsteps) + Start_p;
}
FLOAT vbTween::doTween(FLOAT Start_p, FLOAT Stop_p, DWORD currentStep, DWORD TOTsteps, tweenRepeat loop, EasingFunction easingFunction)
{
	FLOAT Current_p;
	FLOAT p;
	if (loop == twOneShot || loop == twRepeatOnce)
	{
		if (currentStep >= TOTsteps)
			currentStep = TOTsteps;
	}
	else
	{
		if (loop == twRepeat)
			currentStep = (currentStep) % (TOTsteps);
		else if (loop == twYoyo)
		{
			currentStep = ((currentStep % (TOTsteps * 2)) >= TOTsteps) ? ((TOTsteps - 1) - (currentStep % TOTsteps)) : currentStep;
			currentStep %= TOTsteps;
		}
	}
	p = (FLOAT)((double)currentStep / (TOTsteps - 1));
	p = easingFunction(p);
	Current_p = (Stop_p - Start_p) * p + Start_p;
	return Current_p;
}
vbTween::vbTween(BYTE* value, FLOAT Start_p, FLOAT Stop_p, DWORD TOTsteps, tweenRepeat loop, EasingFunction easingFunction, int repeatFor, tween_callback callback, tween_callback callbackKill)
{
	this->valueBYTE = (value);
	init(Start_p, Stop_p, TOTsteps, loop, easingFunction, repeatFor, callback, callbackKill);
}
vbTween::vbTween(WORD* value, FLOAT Start_p, FLOAT Stop_p, DWORD TOTsteps, tweenRepeat loop, EasingFunction easingFunction, int repeatFor, tween_callback callback, tween_callback callbackKill)
{
	this->valueWORD = (value);
	init(Start_p, Stop_p, TOTsteps, loop, easingFunction, repeatFor, callback, callbackKill);
}
vbTween::vbTween(DWORD* value, FLOAT Start_p, FLOAT Stop_p, DWORD TOTsteps, tweenRepeat loop, EasingFunction easingFunction, int repeatFor, tween_callback callback, tween_callback callbackKill)
{
	this->valueDWORD = (value);
	init(Start_p, Stop_p, TOTsteps, loop, easingFunction, repeatFor, callback, callbackKill);
}
vbTween::vbTween(FLOAT* value, FLOAT Start_p, FLOAT Stop_p, DWORD TOTsteps, tweenRepeat loop, EasingFunction easingFunction, int repeatFor, tween_callback callback, tween_callback callbackKill)
{
	this->valueFLOAT = (value);
	init(Start_p, Stop_p, TOTsteps, loop, easingFunction, repeatFor, callback, callbackKill);
}
vbTween::vbTween(int* value, FLOAT Start_p, FLOAT Stop_p, DWORD TOTsteps, tweenRepeat loop, EasingFunction easingFunction, int repeatFor, tween_callback callback, tween_callback callbackKill)
{
	this->valueINT = (value);
	init(Start_p, Stop_p, TOTsteps, loop, easingFunction, repeatFor, callback, callbackKill);
}
vbTween::vbTween(FLOAT Start_p, FLOAT Stop_p, DWORD TOTsteps, tweenRepeat loop, EasingFunction easingFunction, int repeatFor, tween_callback callback, tween_callback callbackKill)
{
	this->valueDWORD = &this->valueTIMER;
	init(Start_p, Stop_p, TOTsteps, loop, easingFunction, repeatFor, callback, callbackKill);
}
vbTween* vbTween::Play()
{
	this->enabled = TRUE;
	return this;
}

vbTween* vbTween::Pause()
{
	this->enabled = FALSE;
	return this;
}

vbTween* vbTween::Restart()
{
	this->Reset();
	this->Play();
	return this;
}

vbTween* vbTween::Stop()
{
	this->enabled = FALSE;
	this->Reset();
	return this;
}

// Complete the execution of the tween to the end, it is transformed to a oneshot
void vbTween::Finish()
{
	this->repeat = twOneShot;
	this->currStep = this->currStep % this->totStep;
}

vbTween* vbTween::Reset()
{
	this->currStep = 0;
	this->repeatFor = this->repeatSet;
	return this;
}

void vbTween::Step()
{
	if (this->enabled == FALSE)
		return;
	if (this->currStep > 0 && this->repeat == twRepeat && this->isFinished())
		this->currStep++; //FIXME

	FLOAT res = doTween(this->startP, this->stopP, this->currStep, this->totStep, this->repeat, this->easingF);
	if (this->valueBYTE != NULL)
		*this->valueBYTE = (BYTE)res;
	else if (this->valueWORD != NULL)
		*this->valueWORD = (WORD)res;
	else if (this->valueDWORD != NULL)
		*this->valueDWORD = (DWORD)res;
	else if (this->valueINT != NULL)
		*this->valueINT = (int)res;
	else if (this->valueFLOAT != NULL)
		*this->valueFLOAT = res;
	this->currStep++;
}

BOOL vbTween::isFinished()
{
	if (this->currStep == 0)
		return FALSE;
	else if (this->currStep == 0 && this->totStep == 0)
		return TRUE;
	return ((this->currStep % this->totStep)==0);
}

BOOL vbTween::isTerminated()
{
	return (this->repeatFor == 0);
}


// TWEENMAP
vbTween* vbTweenMap::addtween(const char* name, vbTween tw)
{
	this->insert(std::pair<const char*, vbTween>(name, tw));
	return &this->operator[](name);
}
vbTween* vbTweenMap::addtimer(const char* name, DWORD TOTsteps, tweenRepeat loop, EasingFunction easingFunction, int numRepeats, tween_callback callback)
{
	//FIXME solve conflicting names inside the map
	this->insert(std::pair<const char*, vbTween>(name, vbTween(0, (FLOAT)TOTsteps, TOTsteps, loop, easingFunction, numRepeats, callback)));
	return &this->operator[](name);
}
vbTween* vbTweenMap::tweenGet(const char* name)
{
	if (this->find(name) == this->end())
		return NULL;
	else
		return &this->operator[](name);
}
void vbTweenMap::killTween(const char* name)
{
	if (this->find(name) != this->end())
		this->erase(name);
}
void vbTweenMap::killAll()
{
	if (this->size() == 0)
		return;
	vbTweenMap::iterator itw = this->begin();
	while (itw != this->end())
	{
		vbTweenMap::iterator toErase = itw;
		itw++;
		this->erase(toErase);
	}
}
void vbTweenMap::stopAll()
{
	if (this->size() == 0)
		return;
	vbTweenMap::iterator itw = this->begin();
	while (itw != this->end())
	{
		itw->second.Stop();
		itw++;
	}
}
void vbTweenMap::stepAll()
{
	if (this->size() == 0)
		return;

	std::vector<vbTween*> nextList;
	vbTweenMap::iterator itw = this->begin();
	while (itw != this->end())
	{
		itw->second.Step();
		if (itw->second.isFinished() && itw->second.repeatFor > 0)
			itw->second.repeatFor--;

		if (itw->second.isFinished())
		{
			if (itw->second.callbackEnd != NULL)
				itw->second.callbackEnd();

			if (itw->second.next && itw->second.repeatFor == 0 && itw->second.repeatSet != 0)
				nextList.push_back(itw->second.next);
			if ((itw->second.repeat == twOneShot) || (itw->second.repeatFor == 0))
				itw = this->erase(itw);
		}
		if (itw != this->end())
			itw++;
	}

	for (WORD i = 0; i < nextList.size(); i++)
	{
		nextList[i]->enabled = TRUE;
		//this->addtween("next", *nextList[i]);
		//nextList[i]->currStep = 1;
	}
}
