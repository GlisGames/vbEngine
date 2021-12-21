#ifndef VBTIMER_H
#define VBTIMER_H

class vbTimer : public vbLivingObject {
private:
	double initTime = GetTime();
	void init();
public:
	vbTimer();
	void update();
	double getTimeAlive();
};
#endif // !VBTIMER_H
