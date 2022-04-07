#include "vbEngine.h"
vbTween::vbTween()
{}

vbTween::~vbTween()
{
	if (this->callbackKill)
		this->callbackKill();
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
FLOAT vbTween::doTween(FLOAT Start_p, FLOAT Stop_p, QWORD currentStep, WORD TOTsteps)
{
	if (currentStep >= TOTsteps)
		currentStep = TOTsteps;
	return (Stop_p - Start_p) * ((FLOAT)currentStep / (FLOAT)TOTsteps) + Start_p;
}
FLOAT vbTween::doTween(FLOAT Start_p, FLOAT Stop_p, QWORD currentStep, DWORD TOTsteps, tweenRepeat loop, EasingFunction easingFunction)
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

/// <summary>
/// Bring the tween instantly to the last step and assign the value to destination
/// </summary>
/// <returns></returns>
vbTween* vbTween::End()
{
	this->currStep = this->totStep;
	FLOAT res = this->stopP;

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
	return this;
}

vbTween* vbTween::Pause()
{
	this->enabled = FALSE;
	return this;
}

vbTween* vbTween::startAfter(FLOAT time)
{
	startDelay = time;
	if (this->isTimeBased)
		startTimer = getMillis();
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

	if (this->currStep > 0 && (this->repeat == twRepeat /*|| this->repeat == twYoyo*/) && this->isFinished())
	{
		if (this->isTimeBased)
			this->currStep += getElapsedMillis();
		else
			this->currStep++; //FIXME baby one more time
	}

	FLOAT res = doTween(this->startP, this->stopP, this->currStep, this->totStep, this->repeat, this->easingF);

	if (this->isTimeBased)
		this->currStep += getElapsedMillis();
	else
		this->currStep++;

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

}

BOOL vbTween::isFinished()
{
	if (this->currStep == 0)
		return FALSE;
	else if (this->currStep == 0 && this->totStep == 0)
		return TRUE;
	if(this->isTimeBased == FALSE)
		return ((this->currStep % this->totStep)==0);
	else
	{
		if (this->repeat == twYoyo)
		{
			if (this->currStep >= (this->repeatSet - this->repeatFor + 1) * this->totStep)
				return TRUE;
			return FALSE;
		}

		if (this->currStep >= this->totStep)
			return TRUE;
		else
			return FALSE;
	}
}

// TWEENMAP
vbTween* vbTweenMap::addtween(string name, vbTween tw)
{
	this->insert(std::pair<string, vbTween>(name, tw));
	return &this->operator[](name);
}
vbTween* vbTweenMap::addtimer(string name, DWORD TOTsteps, tweenRepeat loop, EasingFunction easingFunction, int numRepeats, tween_callback callback)
{
	//FIXME solve conflicting names inside the map
	this->insert(std::pair<string, vbTween>(name, vbTween(0, (FLOAT)TOTsteps, TOTsteps, loop, easingFunction, numRepeats, callback)));
	return &this->operator[](name);
}
vbTween* vbTweenMap::getTween(string name)
{
	if (this->find(name) == this->end())
		return NULL;
	else
		return &this->operator[](name);
}
void vbTweenMap::killTween(string name)
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
		BOOL skip = FALSE;

		if (itw->second.startDelay)
		{
			if (itw->second.isTimeBased)
			{
				if (getMillis() - itw->second.startTimer < itw->second.startDelay)
					skip = TRUE;
				else
					itw->second.startDelay = 0;
			}
			else if (!(itw->second.isTimeBased))
			{
				itw->second.startDelay--;
				if (itw->second.startDelay > 0)
					skip = TRUE;
			}

			if (skip)
			{
				if (itw != this->end()) itw++;
				continue;
			}
		}

		if (itw->second.currStep == 0 && itw->second.callbackStart != NULL)
		{
			itw->second.callbackStart();
			itw->second.callbackStart = NULL;
		}
		itw->second.Step();
		if (itw->second.callbackStep != NULL)
			itw->second.callbackStep();

		BOOL _isFinished = itw->second.isFinished();

		if (_isFinished && itw->second.repeatFor > 0)
		{
			itw->second.repeatFor--;
		}

		if (itw->second.callbackEnd != NULL && _isFinished)
			itw->second.callbackEnd();

		if (_isFinished && itw->second.repeatFor == 0)
			//((itw->second.repeat == twOneShot) || ((itw->second.repeat == twRepeat || itw->second.repeat == twYoyo) && (itw->second.repeatFor == 0))))
		{
			if (itw->second.repeat != twYoyo)
				itw->second.End(); //make sure that the value goes to the end;

			if (itw->second.next)
				nextList.push_back(itw->second.next);
			itw = this->erase(itw);
		}
		else if (itw != this->end())
		{
			if (itw->second.isTimeBased && itw->second.currStep >= itw->second.totStep && itw->second.repeat != twYoyo)
				itw->second.currStep = 0;
			itw++;
		}
	}

	for (WORD i = 0; i < nextList.size(); i++)
	{
		nextList[i]->enabled = TRUE;
		//this->addtween("next", *nextList[i]);
		//nextList[i]->currStep = 1;
	}
}
