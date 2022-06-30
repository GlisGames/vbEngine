#include "vbEngine.h"
QWORD oldFrameMillis = 0;
QWORD frameMillis = 0;
chrono::milliseconds monotonicMillis = 0ms;
QWORD monotonicMillisCount = 0;

void updateFrameMillis()
{
	monotonicMillis = vbTimer::getMonotonicMillis();
	monotonicMillisCount = monotonicMillis.count();
	if (!oldFrameMillis)
		oldFrameMillis = monotonicMillis.count() + 16;
	frameMillis = monotonicMillis.count() - oldFrameMillis;
	oldFrameMillis = monotonicMillis.count();
}

QWORD getMillis()
{
	return monotonicMillisCount;
}

QWORD getElapsedMillis()
{
	if (!frameMillis) frameMillis = 16;
	return frameMillis;
}

// INIT
void vbTimer::init(chrono::milliseconds _duration, timer_callback callback) {
	this->isAlive = TRUE;
	this->initTime = monotonicMillis;
	this->duration = _duration;
	this->callbackEnd = callback;
}
// CTOR
vbTimer::vbTimer(chrono::milliseconds _duration, timer_callback callback) {
	this->init(_duration, callback);
}
// UPDATE
void vbTimer::update(){

	chrono::milliseconds t = monotonicMillis - initTime;
	if (t >= this->duration) {
		this->isTimesUp = TRUE;
		if (this->callbackEnd != NULL) {
			this->callbackEnd();
			this->initTime = monotonicMillis;
		}
		if (this->endLambda != NULL) {
			this->endLambda();
			this->initTime = monotonicMillis;
		}
	}
}
// GETTERS & SETTERS
chrono::milliseconds vbTimer::getInitTime() {
	return this->initTime;
}

chrono::milliseconds vbTimer::getDuration() {
	return this->duration;
}

void vbTimer::setInitTime() {
	this->initTime = monotonicMillis;
}
void vbTimer::setDuration(chrono::milliseconds _duration, timer_callback callback) {
	this->duration = _duration;
	this->callbackEnd = callback;
}
// OTHERS
void vbTimer::reset() {
	this->initTime = monotonicMillis;
	this->isTimesUp = FALSE;
	this->callbackEnd = NULL;
	this->endLambda = NULL;
}

chrono::milliseconds vbTimer::getTimeAlive() {
	return (monotonicMillis - this->initTime);
}