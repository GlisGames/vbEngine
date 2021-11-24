#include "vbEngine.h"
vbTween::vbTween()
{}

void vbTween::init(FLOAT Start_p, FLOAT Stop_p, DWORD TOTsteps, tweenRepeat loop, EasingFunction easingFunction, int repeatFor, tween_callback callback)
{
	this->startP = Start_p;
	this->stopP = Stop_p;
	this->totStep = TOTsteps;
	this->repeat = loop;
	this->easingF = easingFunction;
	this->currStep = 0;
	this->repeatFor = repeatFor;
	this->callbackEnd = callback;
	this->endLambda = NULL;
}
vbTween::vbTween(BYTE* value, FLOAT Start_p, FLOAT Stop_p, DWORD TOTsteps, tweenRepeat loop, EasingFunction easingFunction, int repeatFor, tween_callback callback)
{
	this->valueBYTE = (value);
	init(Start_p, Stop_p, TOTsteps, loop, easingFunction, repeatFor, callback);
}
vbTween::vbTween(WORD* value, FLOAT Start_p, FLOAT Stop_p, DWORD TOTsteps, tweenRepeat loop, EasingFunction easingFunction, int repeatFor, tween_callback callback)
{
	this->valueWORD = (value);
	init(Start_p, Stop_p, TOTsteps, loop, easingFunction, repeatFor, callback);
}
vbTween::vbTween(DWORD* value, FLOAT Start_p, FLOAT Stop_p, DWORD TOTsteps, tweenRepeat loop, EasingFunction easingFunction, int repeatFor, tween_callback callback)
{
	this->valueDWORD = (value);
	init(Start_p, Stop_p, TOTsteps, loop, easingFunction, repeatFor, callback);
}
vbTween::vbTween(FLOAT* value, FLOAT Start_p, FLOAT Stop_p, DWORD TOTsteps, tweenRepeat loop, EasingFunction easingFunction, int repeatFor, tween_callback callback)
{
	this->valueFLOAT = (value);
	init(Start_p, Stop_p, TOTsteps, loop, easingFunction, repeatFor, callback);
}
vbTween::vbTween(int* value, FLOAT Start_p, FLOAT Stop_p, DWORD TOTsteps, tweenRepeat loop, EasingFunction easingFunction, int repeatFor, tween_callback callback)
{
	this->valueINT = (value);
	init(Start_p, Stop_p, TOTsteps, loop, easingFunction, repeatFor, callback);
}
vbTween::vbTween(FLOAT Start_p, FLOAT Stop_p, DWORD TOTsteps, tweenRepeat loop, EasingFunction easingFunction, int repeatFor, tween_callback callback)
{
	this->valueDWORD = &this->valueTIMER;
	init(Start_p, Stop_p, TOTsteps, loop, easingFunction, repeatFor, callback);
}
vbTween* vbTween::Enable()
{
	this->enabled = TRUE;
	return this;
}

vbTween* vbTween::Pause()
{
	this->enabled = FALSE;
	return this;
}

vbTween* vbTween::Play()
{
	this->Reset();
	this->Enable();
	return this;
}

vbTween* vbTween::Stop()
{
	this->enabled = FALSE;
	this->Reset();
	return this;
}

/// <summary>
/// Complete the execution of the tween to the end, it is transformed to a oneshot
/// </summary>
void vbTween::Finish()
{
	//this->currStep = this->totStep;
	//this->repeatFor = 0;
	this->repeat = twOneShot;
	this->currStep = this->currStep % this->totStep;
}

vbTween* vbTween::Reset()
{
	this->currStep = 0;
	this->repeatFor = 0;
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
