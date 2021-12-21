#ifndef VBTIMER_H
#define VBTIMER_H

class vbTimer : public vbLivingObject {
private:
	double initTime = GetTime();
	double duration = 0;
	void init(double _duration);
public:
	vbTimer(double _duration = 1);
	void update();
	void reset();
	double getTimeAlive();
};
#endif // !VBTIMER_H
