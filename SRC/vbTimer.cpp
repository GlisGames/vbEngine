#include "vbEngine.h"

// INIT
void vbTimer::init(double _duration, timer_callback callback) {
	this->isAlive = TRUE;
	this->initTime = GetTime();
	this->duration = _duration;
	this->callbackEnd = callback;
}
// CTOR
vbTimer::vbTimer(double _duration, timer_callback callback) {
	this->init(_duration, callback);
}
// UPDATE
void vbTimer::update(){
	double t = this->getTimeAlive();
	if (t >= this->duration) {
		this->isTimesUp = TRUE;
	}

	if (this->isTimesUp) {
		if (this->callbackEnd != NULL) {
			this->callbackEnd();
			this->initTime = GetTime();
		}
		if (this->endLambda != NULL) {
			this->endLambda();
			this->initTime = GetTime();
		}
		this->isTimesUp = FALSE;
	}
}
// GETTERS & SETTERS
double vbTimer::getInitTime() {
	return this->initTime;
}
double vbTimer::getDuration() {
	return this->duration;
}
void vbTimer::setInitTime() {
	this->initTime = GetTime();
}
void vbTimer::setDuration(double _duration, timer_callback callback) {
	this->duration = _duration;
	this->callbackEnd = callback;
}
// OTHERS
void vbTimer::reset() {
	this->initTime = GetTime();
	this->isTimesUp = FALSE;
	this->callbackEnd = NULL;
	this->endLambda = NULL;
}
double vbTimer::getTimeAlive() {
	return (GetTime() - this->initTime);
}
//template <class callable, class... arguments>
//void vbTimer::later(bool async, callable&& f, arguments&&... args) {
//	std::function<typename std::result_of<callable(arguments...)>::type()> task(std::bind(std::forward<callable>(f), std::forward<arguments>(args)...));
//
//    if (async) {
//        std::thread([this->duration, task]() {
//            std::this_thread::sleep_for(std::chrono::seconds(this->duration));
//            task();
//        }).detach();
//    }
//    else {
//        std::this_thread::sleep_for(std::chrono::seconds(this->duration));
//        task();
//    }
//}