#ifndef VBGPIO_H
#define VBGPIO_H
#ifdef PLATFORM_RASPBERRY
#include <wiringPi.h>
#else
#include "wiringpi/wiringPi.h"
#endif
#include "basetypes.h"
#include <functional>
typedef void (*GPIOcallback)(void);

class vbGPIO {
private:
	WORD pin_number = 0;
	WORD pin_mode = INPUT;
	WORD pull_mode = PUD_OFF;
	WORD isr_edge = INT_EDGE_SETUP;
public:
	hwButton buttonID = hwButton::BUTTON_NONE;
	std::function<void()> callbackLambda = NULL;
	/// <summary>
	/// Set the callback when the edge is triggered
	/// </summary>
	/// <param name="edge">INT_EDGE_FALLING or INT_EDGE_RISING or INT_EDGE_BOTH</param>
	/// <param name="f">lamba function to be set</param>
	/// <returns></returns>
	vbGPIO* setCallback(WORD edge, GPIOcallback f) {
		callbackLambda = f;
		isr_edge = edge;
#ifdef PLATFORM_RASPBERRY
		wiringPiISR(pin_number, isr_edge, f);
#endif // PLATFORM_RASPBERRY
		return this;
	}

	/// <summary>
	/// Init GPIO pin
	/// </summary>
	/// <param name="_pin_number">pin must be between 0-63</param>
	/// <param name="_pinmode">OUTPUT or INPUT</param>
	vbGPIO(WORD _pin_number, WORD _pinmode, hwButton btn = hwButton::BUTTON_NONE)
	{
		pin_number = _pin_number;
		pin_mode = _pinmode;
#ifdef PLATFORM_RASPBERRY
		pinMode(_pin_number, _pinmode);
#endif
		buttonID = btn;
	}

	/// <summary>
	/// set internal pullups
	/// </summary>
	/// <param name="pull">PUD_DOWN or PUD_UP or PUD_OFF</param>
	void setPullUpDown(WORD pull)
	{
#ifdef PLATFORM_RASPBERRY
		pullUpDnControl(pin_number, pull);
#endif
	}

	/// <summary>
	/// read the state of a GPIO
	/// </summary>
	/// <returns>1 if high, 0 if low</returns>
	int readGPIO()
	{
#ifdef PLATFORM_RASPBERRY
		return digitalRead(pin_number);
#else
		return 1;
#endif
	}

	/// <summary>
	/// set the state of the GPIO
	/// </summary>
	/// <param name="value">HIGH or LOW</param>
	void writeGPIO(BOOL value)
	{
#ifdef PLATFORM_RASPBERRY
		if(this->pin_mode == OUTPUT)
			digitalWrite(pin_number, value);
#endif
	}
};
#endif