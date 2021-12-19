#ifndef VBGPIO_H
#define VBGPIO_H
#ifdef PLATFORM_RASPBERRY
#include <wiringPi.h>
#else
#include "wiringpi/wiringPi.h"
#endif
#include "basetypes.h"
#include <functional>
#include <thread>
#include <mutex>
typedef void (*GPIOcallback)(void);

class vbGPIO {
private:
	int buttonState = 0;         // current state of the button
	int lastButtonState = 0;     // previous state of the button
	int lastButtonStateDebounce = 0;     // previous state of the button
	unsigned long lastDebounceTime = 0;
	WORD debounceDelay = 25;
	WORD pin_number = 0;
	WORD pin_mode = INPUT;
	WORD pull_mode = PUD_OFF;
	WORD isr_edge = INT_EDGE_SETUP;
	mutex gpioMutex;
	mutex pressedMutex;
public:
	BOOL pressedState = FALSE;
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
		buttonState = lastButtonState = digitalRead(pin_number);
#endif
		buttonID = btn;
	}

	/// <summary>
	/// Set the debounce delay, defaut is 25ms
	/// </summary>
	/// <param name="milliseconds">time in milliseconds</param>
	void setDebounceDelay(WORD milliseconds)
	{
		debounceDelay = milliseconds;
	}

	/// <summary>
	/// set internal pullups
	/// </summary>
	/// <param name="pull">PUD_DOWN or PUD_UP or PUD_OFF</param>
	void setPullUpDown(WORD pull)
	{
		pull_mode = pull;
#ifdef PLATFORM_RASPBERRY
		pullUpDnControl(pin_number, pull);
#endif
	}

	BOOL isPressed()
	{
		BOOL ret = FALSE;
		pressedMutex.lock();
		ret = pressedState;
		pressedState = FALSE; //reset
		pressedMutex.unlock();
		return ret;
	}

	void pollState()
	{
#ifdef PLATFORM_RASPBERRY
#endif
		int reading = digitalRead(pin_number);

		// If the switch changed, due to noise or pressing:
		if (reading != lastButtonStateDebounce) {
			// reset the debouncing timer
			lastDebounceTime = millis();
		}

		if ((millis() - lastDebounceTime) > debounceDelay) {
			// whatever the reading is at, it's been there for longer than the debounce
			// delay, so take it as the actual current state:

			// if the button state has changed:
			if (reading != buttonState) {
				gpioMutex.lock();
				buttonState = reading;
				gpioMutex.unlock();
			}
		}
		lastButtonStateDebounce = reading;
		
		if (buttonState != lastButtonState)
		{
			pressedMutex.lock();
			if (buttonState == LOW)
				pressedState = TRUE;
			//else
			//	pressedState = FALSE;
			pressedMutex.unlock();
		}
		lastButtonState = buttonState;
	}

	int digitalPinRead()
	{
		return digitalRead(pin_number);
	}

	int readGPIO()
	{
		int ret = 0;
#ifdef PLATFORM_RASPBERRY
		//return digitalRead(pin_number);
		gpioMutex.lock();
		ret = buttonState;
		gpioMutex.unlock();
#endif
		return ret;
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