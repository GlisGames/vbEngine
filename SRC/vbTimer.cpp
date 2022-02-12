#include "vbEngine.h"

// INIT
void vbTimer::init(chrono::milliseconds _duration, timer_callback callback) {
	this->isAlive = TRUE;
	this->initTime = vbTimer::getMillis();
	this->duration = _duration;
	this->callbackEnd = callback;
}
// CTOR
vbTimer::vbTimer(chrono::milliseconds _duration, timer_callback callback) {
	this->init(_duration, callback);
}
// UPDATE
void vbTimer::update(){
	chrono::milliseconds t = vbTimer::getMillis();
	if (t >= this->duration) {
		this->isTimesUp = TRUE;
	}

	if (this->isTimesUp) {
		if (this->callbackEnd != NULL) {
			this->callbackEnd();
			this->initTime = vbTimer::getMillis();
		}
		if (this->endLambda != NULL) {
			this->endLambda();
			this->initTime = vbTimer::getMillis();
		}
		this->isTimesUp = FALSE;
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
	this->initTime = vbTimer::getMillis();
}
void vbTimer::setDuration(chrono::milliseconds _duration, timer_callback callback) {
	this->duration = _duration;
	this->callbackEnd = callback;
}
// OTHERS
void vbTimer::reset() {
	this->initTime = vbTimer::getMillis();
	this->isTimesUp = FALSE;
	this->callbackEnd = NULL;
	this->endLambda = NULL;
}

chrono::milliseconds vbTimer::getTimeAlive() {
	return (vbTimer::getMillis() - this->initTime);
}