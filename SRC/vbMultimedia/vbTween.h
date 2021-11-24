#ifndef VBTWEEN_H
#define VBTWEEN_H

#include "basetypes.h"
#include "vbEasing.h"
#include <functional>

enum tweenRepeat
{
	twOneShot = 0, //Do once and then erase the tween from memory CAUTION!
	twRepeat = 1, //Repeats from start to end
	twYoyo = 2, //Repeats from start to end then from end to start
	twRepeatOnce = 3 //Repeats from start to end only once
};
typedef void (*tween_callback) ();
class vbTween;
class vbTween
{
private:
	void init(FLOAT Start_p, FLOAT Stop_p, DWORD TOTsteps, tweenRepeat loop, EasingFunction easingFunction, int repeatFor, tween_callback callback);
public:
	static FLOAT doTween(FLOAT Start_p, FLOAT Stop_p, WORD currentStep, WORD TOTsteps)
	{
		if (currentStep >= TOTsteps)
			currentStep = TOTsteps;
		return (Stop_p - Start_p) * ((FLOAT)currentStep / (FLOAT)TOTsteps) + Start_p;
	}
	static FLOAT doTween(FLOAT Start_p, FLOAT Stop_p, DWORD currentStep, DWORD TOTsteps, tweenRepeat loop, EasingFunction easingFunction)
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
		p = (FLOAT)((double)currentStep / (TOTsteps-1));
		p = easingFunction(p);
		Current_p = (Stop_p - Start_p) * p + Start_p;
		return Current_p;
	}
	BOOL enabled = TRUE;
	DWORD currStep = 0;
	DWORD totStep = 1;
	FLOAT startP = 0;
	FLOAT stopP = 0;
	int repeatFor = -1;
	BYTE *valueBYTE = NULL;
	WORD *valueWORD = NULL;
	DWORD *valueDWORD = NULL;
	FLOAT *valueFLOAT = NULL;
	DWORD valueTIMER = NULL;
	tween_callback callbackEnd = NULL;
	int *valueINT = NULL;
	tweenRepeat repeat = twYoyo;
	EasingFunction easingF = LinearInterpolation;
	std::function<void()> endLambda = NULL;
	vbTween* endLambdaSet(std::function<void()> f) {
		this->endLambda = f;
		return this;
	}
	vbTween();
	vbTween(BYTE *value, FLOAT Start_p, FLOAT Stop_p, DWORD TOTsteps, tweenRepeat loop = twYoyo, EasingFunction easingFunction = LinearInterpolation,  int repeatFor = -1, tween_callback callback = NULL);
	vbTween(WORD *value, FLOAT Start_p, FLOAT Stop_p, DWORD TOTsteps, tweenRepeat loop = twYoyo, EasingFunction easingFunction = LinearInterpolation,  int repeatFor = -1, tween_callback callback = NULL);
	vbTween(DWORD *value, FLOAT Start_p, FLOAT Stop_p, DWORD TOTsteps, tweenRepeat loop = twYoyo, EasingFunction easingFunction = LinearInterpolation, int repeatFor =  -1, tween_callback callback = NULL);
	vbTween(FLOAT *value, FLOAT Start_p, FLOAT Stop_p, DWORD TOTsteps, tweenRepeat loop = twYoyo, EasingFunction easingFunction = LinearInterpolation, int repeatFor =  -1, tween_callback callback = NULL);
	vbTween(int *value, FLOAT Start_p, FLOAT Stop_p, DWORD TOTsteps, tweenRepeat loop = twYoyo, EasingFunction easingFunction = LinearInterpolation, int repeatFor =  -1, tween_callback callback = NULL);
	vbTween(FLOAT Start_p, FLOAT Stop_p, DWORD TOTsteps, tweenRepeat loop = twOneShot, EasingFunction easingFunction = LinearInterpolation, int repeatFor =  -1, tween_callback callback = NULL);
	vbTween* Enable();
	vbTween* Stop();
	vbTween* Pause();
	vbTween* Play();
	vbTween* Reset();
	void Step();
	void Finish();
	BOOL isFinished();
	vbTween* next = NULL;
	vbTween* addNext(vbTween* n)
	{
		n->enabled = false;
		next = n;
		return n;
	}
};

class vbTweenMap : public std::map<const char*, vbTween>
{
public:
	void killTween(const char* name)
	{
		if (this->find(name) != this->end())
			this->erase(name);
	}

	void killAll()
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

	template <typename T>
	vbTween* addtween(const char* name, T* value, FLOAT Start_p, FLOAT Stop_p, DWORD TOTsteps, tweenRepeat loop = twYoyo, EasingFunction easingFunction = LinearInterpolation, int numRepeats = -1, tween_callback callback = NULL)
	{
		//FIXME solve conflicting names inside the map
		this->insert(std::pair<const char*, vbTween>(name, vbTween(value, Start_p, Stop_p, TOTsteps, loop, easingFunction, numRepeats, callback)));
		return &this->operator[](name);
	};

	vbTween* addtimer(const char* name, DWORD TOTsteps, tweenRepeat loop = twOneShot, EasingFunction easingFunction = LinearInterpolation, int numRepeats = -1, tween_callback callback = NULL)
	{
		//FIXME solve conflicting names inside the map
		this->insert(std::pair<const char*, vbTween>(name, vbTween(0, (FLOAT)TOTsteps, TOTsteps, loop, easingFunction, numRepeats, callback)));
		return &this->operator[](name);
	};
	vbTween *addtween(const char* name, vbTween tw)
	{
		this->insert(std::pair<const char*, vbTween>(name, tw));
		return &this->operator[](name);
	};

	vbTween* tweenGet(const char* name)
	{
		if (this->find(name) == this->end())
			return NULL;
		else
			return &this->operator[](name);
	}

	void stopAll()
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

	void stepAll()
	{
		if (this->size() == 0)
			return;

		std::vector<vbTween*> nextList;
		vbTweenMap::iterator itw = this->begin();
		while (itw != this->end())
		{
			itw->second.Step();
			if (itw->second.isFinished() && itw->second.repeatFor != -1)
				itw->second.repeatFor--;

			if (itw->second.isFinished())
			{
				if (itw->second.callbackEnd != NULL)
					itw->second.callbackEnd();
				if (itw->second.endLambda != NULL)
					itw->second.endLambda();

				if (itw->second.next)
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
};

//typedef std::map<const char *, vbTween> vbTweenMap;
#endif
