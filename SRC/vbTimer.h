#ifndef VBTIMER_H
#define VBTIMER_H
#include <functional>


typedef void (*timer_callback) ();
class vbTimer : public vbGraphicObject {
private:
	double initTime = GetTime();
	double duration = 0;
	bool isTimesUp = FALSE;
	void init(double _duration, timer_callback callback);
public:
	timer_callback callbackEnd = NULL;
	std::function<void()> endLambda = NULL;
	vbTimer* endLambdaSet(std::function<void()> f) {
		this->endLambda = f;
		return this;
	}

	vbTimer(double _duration = 1, timer_callback callback = NULL);
	void update();
	void reset();
	double getTimeAlive();
	double getInitTime();
	double getDuration();
	void setDuration(double _duration, timer_callback callback = NULL);

	//template <class callable, class... arguments>
	//void later(bool async, callable&& f, arguments&&... args); // TESTING Thread safe with callable 
};
#endif // !VBTIMER_H
