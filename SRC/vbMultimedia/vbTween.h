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

typedef std::function<void()> tween_callback;

class vbTween
{
private:
	void init(FLOAT Start_p, FLOAT Stop_p, DWORD TOTsteps, tweenRepeat loop, EasingFunction easingFunction, int repeatFor, tween_callback callback, tween_callback callbackKill);
public:
	static FLOAT doTween(FLOAT Start_p, FLOAT Stop_p, QWORD currentStep, WORD TOTsteps);
	static FLOAT doTween(FLOAT Start_p, FLOAT Stop_p, QWORD currentStep, DWORD TOTsteps, tweenRepeat loop, EasingFunction easingFunction);
	BOOL enabled = TRUE;
	QWORD currStep = 0;
	DWORD totStep = 1;
	FLOAT startP = 0;
	FLOAT stopP = 0;
	FLOAT startDelay = 0;
	QWORD startTimer = 0;
	BOOL isTimeBased = TRUE;
	int repeatFor = 0;
	int repeatSet = 0; //initial repeat value that has been set
	BYTE *valueBYTE = NULL;
	WORD *valueWORD = NULL;
	DWORD *valueDWORD = NULL;
	FLOAT *valueFLOAT = NULL;
	DWORD *valueTIMER = NULL;
	tween_callback callbackEnd = NULL; //called every time the tween end one cycle
	tween_callback callbackKill = NULL; //called when the tween finished its last cycle, before being deallocated
	tween_callback callbackStart = NULL; //called when the tween finished its last cycle, before being deallocated
	tween_callback callbackStep = NULL; //called when the tween finished its last cycle, before being deallocated
	int *valueINT = NULL;
	tweenRepeat repeat = twYoyo;
	EasingFunction easingF = LinearInterpolation;
	vbTween* startAfter(FLOAT time);
	vbTween* endLambdaSet(tween_callback f) {
		this->callbackEnd = f;
		return this;
	}

	/// <summary>
	/// set a callback that is called every time the tween current step is at zero
	/// </summary>
	/// <param name="f"></param>
	/// <returns></returns>
	vbTween* onStart(tween_callback f) {
		this->callbackStart = f;
		return this;
	}
	vbTween* onStep(tween_callback f) {
		this->callbackStep = f;
		return this;
	}
	vbTween* killLambdaSet(tween_callback f) {
		this->callbackKill = f;
		return this;
	}
	vbTween* setTimeBased(BOOL _isTimebased)
	{
		this->isTimeBased = _isTimebased;
		return this;
	};
	vbTween();
	~vbTween();
	vbTween(BYTE *value, FLOAT Start_p, FLOAT Stop_p, DWORD TOTsteps, tweenRepeat loop = twYoyo, EasingFunction easingFunction = LinearInterpolation,  int repeatFor = 0, tween_callback callback = NULL, tween_callback callbackKill = NULL);
	vbTween(WORD *value, FLOAT Start_p, FLOAT Stop_p, DWORD TOTsteps, tweenRepeat loop = twYoyo, EasingFunction easingFunction = LinearInterpolation,  int repeatFor = 0, tween_callback callback = NULL, tween_callback callbackKill = NULL);
	vbTween(DWORD *value, FLOAT Start_p, FLOAT Stop_p, DWORD TOTsteps, tweenRepeat loop = twYoyo, EasingFunction easingFunction = LinearInterpolation, int repeatFor = 0, tween_callback callback = NULL, tween_callback callbackKill = NULL);
	vbTween(FLOAT *value, FLOAT Start_p, FLOAT Stop_p, DWORD TOTsteps, tweenRepeat loop = twYoyo, EasingFunction easingFunction = LinearInterpolation, int repeatFor = 0, tween_callback callback = NULL, tween_callback callbackKill = NULL);
	vbTween(int *value, FLOAT Start_p, FLOAT Stop_p, DWORD TOTsteps, tweenRepeat loop = twYoyo, EasingFunction easingFunction = LinearInterpolation, int repeatFor = 0, tween_callback callback = NULL, tween_callback callbackKill = NULL);
	vbTween(FLOAT Start_p, FLOAT Stop_p, DWORD TOTsteps, tweenRepeat loop = twOneShot, EasingFunction easingFunction = LinearInterpolation, int repeatFor = 0, tween_callback callback = NULL, tween_callback callbackKill = NULL);
	vbTween* Play();
	vbTween* Stop();
	vbTween* End();
	vbTween* Pause();
	vbTween* Restart();
	vbTween* Reset();
	void Step();
	BOOL isFinished();
	vbTween* next = NULL;
	vbTween* addNext(vbTween* n)
	{
		n->enabled = false;
		next = n;
		return n;
	}
};

class vbTweenMap : public std::map<string, vbTween>
{
public:
	template <typename T>
	vbTween* addtween(string name, T* value, FLOAT Start_p, FLOAT Stop_p, DWORD TOTsteps, tweenRepeat loop = twYoyo, EasingFunction easingFunction = LinearInterpolation, int numRepeats = 0, tween_callback callback = NULL)
	{
		//FIXME solve conflicting names inside the map
		this->insert(std::pair<string, vbTween>(name, vbTween(value, Start_p, Stop_p, TOTsteps, loop, easingFunction, numRepeats, callback)));
		return &this->operator[](name);
	};
	vbTween* addtween(string name, vbTween tw);
	vbTween* addtimer(string name, DWORD TOTsteps, tweenRepeat loop = twOneShot, EasingFunction easingFunction = LinearInterpolation, int numRepeats = 0, tween_callback callback = NULL);
	vbTween* getTween(string name);
	void killTween(string name);
	void killAll();
	void stopAll();
	void stepAll();
};

//typedef std::map<const char *, vbTween> vbTweenMap;
#endif
