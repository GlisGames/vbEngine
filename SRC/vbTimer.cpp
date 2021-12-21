#include "vbEngine.h"

void vbTimer::init(double _duration) {
	this->isAlive = TRUE;
	this->initTime = GetTime();
	this->duration = _duration;
}

vbTimer::vbTimer(double _duration) {
	this->init(_duration);
}

void vbTimer::update(){
	if (this->getTimeAlive() > this->duration) {
		printf("TIME'S UP");
		this->reset();
	}
}

void vbTimer::reset() {
	this->initTime = GetTime();
}

double vbTimer::getTimeAlive() {
	return (GetTime() - this->initTime);
}
