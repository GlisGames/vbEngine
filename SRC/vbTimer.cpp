#include "vbEngine.h"

void vbTimer::init() {
	this->isAlive = TRUE;
	double initTime = GetTime();
}

vbTimer::vbTimer() {
	this->init();
}

void vbTimer::update(){
}

double vbTimer::getTimeAlive() {
	return (GetTime() - this->initTime);
}
