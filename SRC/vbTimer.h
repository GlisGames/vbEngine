#ifndef VBTIMER_H
#define VBTIMER_H
#include <functional>
#include <chrono>

void updateFrameMillis();

QWORD getElapsedMillis();

typedef void (*timer_callback) ();
class vbTimer : public vbGraphicObject {
private:
	chrono::milliseconds initTime = 0ms;
	//double duration = 0;
	chrono::milliseconds duration = 0ms;
	bool isTimesUp = FALSE;
	void init(chrono::milliseconds _duration, timer_callback callback);
public:
	static chrono::milliseconds getMillis()
	{
		return std::chrono::duration_cast<std::chrono::milliseconds>(
			std::chrono::system_clock::now().time_since_epoch()
			);
	}
	static chrono::microseconds getMicros()
	{
		return std::chrono::duration_cast<std::chrono::microseconds>(
			std::chrono::high_resolution_clock::now().time_since_epoch()
			);
	}

	timer_callback callbackEnd = NULL;
	std::function<void()> endLambda = NULL;
	vbTimer* endLambdaSet(std::function<void()> f) {
		this->endLambda = f;
		return this;
	}

	vbTimer(chrono::milliseconds _duration = 1ms, timer_callback callback = NULL);
	void update();
	void reset();
	chrono::milliseconds getTimeAlive();
	chrono::milliseconds getInitTime();
	chrono::milliseconds getDuration();
	void setInitTime();
	void setDuration(chrono::milliseconds _duration, timer_callback callback = NULL);

	//template <class callable, class... arguments>
	//void later(bool async, callable&& f, arguments&&... args); // TESTING Thread safe with callable 
};
#endif // !VBTIMER_H
