/*!
	@file easing.cpp

	@copyright Nazionale Elettronica

	@brief Implementazione delle funzioni di easing

	@details le funzioni di interpolazione sono funzioni del genere y = f(x), dove dato un valore di x (dominio) compreso tra 0.0 (inizio dell'animazione) e 1.0 (fine dell'animazione) 
	@details restituiscono un valore di y, i cui estremi sono f(0) = 0.0 e f(1.0) = 1.0, ma nell'intervallo possono assumere qualsiasi valore.
	Servono, applicate a funzioni di tween, per calcolare percorsi o eseguire traiettorie lineari e non
*/
#include <math.h>
#include "vbEasing.h"

//! @brief Interpolazione lineare (y = x)
//! @param p progresso x dell'interpolazione (range 0.0-1.0)
//! @return progresso y dell'interpolazione
float LinearInterpolation(float p)
{
	return p;
}
//---------------------------------------------------------------------
//! @brief Interpolazione parabolica in ingresso (y = x^2)
//! @param p progresso x dell'interpolazione (range 0.0-1.0)
//! @return progresso y dell'interpolazione
float QuadraticEaseIn(float p)
{
	return p * p;
}
//---------------------------------------------------------------------
//! @brief Interpolazione parabolica in uscita (y = -x^2 + 2x)
//! @param p progresso x dell'interpolazione (range 0.0-1.0)
//! @return progresso y dell'interpolazione
float QuadraticEaseOut(float p)
{
	return -(p * (p - 2));
}
//---------------------------------------------------------------------
//! @brief Interpolazione parabolica in ingresso e uscita (y = (1/2)((2x)^2) in [0, 0.5), y = -(1/2)((2x-1)*(2x-3) - 1) in [0.5, 1])
//! @param p progresso x dell'interpolazione (range 0.0-1.0)
//! @return progresso y dell'interpolazione
float QuadraticEaseInOut(float p)
{
	if (p < 0.5)
	{
		return 2 * p * p;
	}
	else
	{
		return (-2 * p * p) + (4 * p) - 1;
	}
}
//---------------------------------------------------------------------
//! @brief Interpolazione cubica in ingresso (y = x^3)
//! @param p progresso x dell'interpolazione (range 0.0-1.0)
//! @return progresso y dell'interpolazione
float CubicEaseIn(float p)
{
	return p * p * p;
}
//---------------------------------------------------------------------
//! @brief Interpolazione cubica in uscita (y = (x - 1)^3 + 1)
//! @param p progresso x dell'interpolazione (range 0.0-1.0)
//! @return progresso y dell'interpolazione
float CubicEaseOut(float p)
{
	float f = (p - 1);
	return f * f * f + 1;
}
//---------------------------------------------------------------------
//! @brief Interpolazione cubica in ingresso e uscita ( y = (1/2)((2x)^3) in [0, 0.5), y = (1/2)((2x-2)^3 + 2) in [0.5, 1])
//! @param p progresso x dell'interpolazione (range 0.0-1.0)
//! @return progresso y dell'interpolazione
float CubicEaseInOut(float p)
{
	if (p < 0.5)
	{
		return 4 * p * p * p;
	}
	else
	{
		float f = ((2 * p) - 2);
		return 0.5f * f * f * f + 1;
	}
}
//---------------------------------------------------------------------
//! @brief Interpolazione quartica in ingresso (y = x^4)
//! @param p progresso x dell'interpolazione (range 0.0-1.0)
//! @return progresso y dell'interpolazione
float QuarticEaseIn(float p)
{
	return p * p * p * p;
}
//---------------------------------------------------------------------
//! @brief Interpolazione quartica in uscita (y = 1 - (x - 1)^4)
//! @param p progresso x dell'interpolazione (range 0.0-1.0)
//! @return progresso y dell'interpolazione
float QuarticEaseOut(float p)
{
	float f = (p - 1);
	return f * f * f * (1 - p) + 1;
}
//---------------------------------------------------------------------
//! @brief Interpolazione quartica in ingresso e uscita ( y = (1/2)((2x)^4) in [0, 0.5), y = -(1/2)((2x-2)^4 - 2) in [0.5, 1])
//! @param p progresso x dell'interpolazione (range 0.0-1.0)
//! @return progresso y dell'interpolazione
float QuarticEaseInOut(float p)
{
	if (p < 0.5)
	{
		return 8 * p * p * p * p;
	}
	else
	{
		float f = (p - 1);
		return -8 * f * f * f * f + 1;
	}
}
//---------------------------------------------------------------------
//! @brief Interpolazione quintica in ingresso (y = x^5)
//! @param p progresso x dell'interpolazione (range 0.0-1.0)
//! @return progresso y dell'interpolazione
float QuinticEaseIn(float p)
{
	return p * p * p * p * p;
}
//---------------------------------------------------------------------
//! @brief Interpolazione quintica in uscita (y = (x - 1)^5 + 1)
//! @param p progresso x dell'interpolazione (range 0.0-1.0)
//! @return progresso y dell'interpolazione
float QuinticEaseOut(float p)
{
	float f = (p - 1);
	return f * f * f * f * f + 1;
}
//---------------------------------------------------------------------
//! @brief Interpolazione quintica in ingresso e uscita ( y = (1/2)((2x)^5) in [0, 0.5), y = (1/2)((2x-2)^5 + 2) in [0.5, 1])
//! @param p progresso x dell'interpolazione (range 0.0-1.0)
//! @return progresso y dell'interpolazione
float QuinticEaseInOut(float p)
{
	if (p < 0.5)
	{
		return 16 * p * p * p * p * p;
	}
	else
	{
		float f = ((2 * p) - 2);
		return  0.5f * f * f * f * f * f + 1;
	}
}
//---------------------------------------------------------------------
//! @brief Interpolazione sinusoidale in ingresso (y = sin((x-1) * pi/2) + 1)
//! @param p progresso x dell'interpolazione (range 0.0-1.0)
//! @return progresso y dell'interpolazione
float SineEaseIn(float p)
{
	return (float)(sin((p - 1) * (float)M_PI_2) + 1);
}
//---------------------------------------------------------------------
//! @brief Interpolazione sinusoidale in uscita (y = sin(x * pi/2))
//! @param p progresso x dell'interpolazione (range 0.0-1.0)
//! @return progresso y dell'interpolazione
float SineEaseOut(float p)
{
	return (float)(sin(p * (float)M_PI_2));
}
//---------------------------------------------------------------------
//! @brief Interpolazione sinusoidale in ingresso e uscita (y = 0.5 * (1 - cos(x * pi/2))
//! @param p progresso x dell'interpolazione (range 0.0-1.0)
//! @return progresso y dell'interpolazione
float SineEaseInOut(float p)
{
	return (float)(0.5f * (1 - cos(p * (float)M_PI)));
}
//---------------------------------------------------------------------
//! @brief Interpolazione circolare (circolo unitario) in ingresso (y = 1 - sqrt(1 - x^2)
//! @param p progresso x dell'interpolazione (range 0.0-1.0)
//! @return progresso y dell'interpolazione
float CircularEaseIn(float p)
{
	return (float)(1 - sqrt(1 - (p * p)));
}
//---------------------------------------------------------------------
//! @brief Interpolazione circolare (circolo unitario) in uscita (y = sqrt(2x - x^2))
//! @param p progresso x dell'interpolazione (range 0.0-1.0)
//! @return progresso y dell'interpolazione
float CircularEaseOut(float p)
{
	return (float)(sqrt((2 - p) * p));
}
//---------------------------------------------------------------------
// Modeled after the piecewise circular function
// y = (1/2)(1 - sqrt(1 - 4x^2))           ; [0, 0.5)
// y = (1/2)(sqrt(-(2x - 3)*(2x - 1)) + 1) ; [0.5, 1]

//! @brief Interpolazione circolare (circolo unitario) in ingresso e uscita ( y =  (1/2)(1 - sqrt(1 - 4x^2)) in [0, 0.5), y = (1/2)(sqrt(-(2x - 3)*(2x - 1)) + 1) in [0.5, 1])
//! @param p progresso x dell'interpolazione (range 0.0-1.0)
//! @return progresso y dell'interpolazione
float CircularEaseInOut(float p)
{
	if (p < 0.5f)
	{
		return (float)(0.5f * (1 - sqrt(1 - 4 * (p * p))));
	}
	else
	{
		return (float)(0.5f * (sqrt(-((2 * p) - 3) * ((2 * p) - 1)) + 1));
	}
}
//---------------------------------------------------------------------
//! @brief Interpolazione esponenziale in ingresso ( y = 2^(10(x - 1) )
//! @param p progresso x dell'interpolazione (range 0.0-1.0)
//! @return progresso y dell'interpolazione
float ExponentialEaseIn(float p)
{
	return (float)((p == 0.0f) ? p : pow(2, 10 * (p - 1)));
}
//---------------------------------------------------------------------
//! @brief Interpolazione esponenziale in uscita ( y = -2^(-10x) + 1 )
//! @param p progresso x dell'interpolazione (range 0.0-1.0)
//! @return progresso y dell'interpolazione
float ExponentialEaseOut(float p)
{
	return (float)((p == 1.0f) ? p : 1 - pow(2, -10 * p));
}
//---------------------------------------------------------------------
//! @brief Interpolazione esponenziale in ingresso e uscita ( y = (1/2)2^(10(2x - 1)) in [0, 0.5), y = -(1/2)*2^(-10(2x - 1))) + 1 in [0.5, 1])
//! @param p progresso x dell'interpolazione (range 0.0-1.0)
//! @return progresso y dell'interpolazione
float ExponentialEaseInOut(float p)
{
	if (p == 0.0f || p == 1.0f) return p;

	if (p < 0.5f)
	{
		return (float)(0.5f * pow(2, (20 * p) - 10));
	}
	else
	{
		return (float)(-0.5f * pow(2, (-20 * p) + 10) + 1);
	}
}
//---------------------------------------------------------------------
//! @brief Interpolazione sinusoidale smorzata in ingresso (y = sin(13pi/2*x) * 2^(10 * (x - 1)))
//! @param p progresso x dell'interpolazione (range 0.0-1.0)
//! @return progresso y dell'interpolazione
float ElasticEaseIn(float p)
{
	return (float)(sin(13 * (float)M_PI_2 * p) * pow(2, 10 * (p - 1)));
}
//---------------------------------------------------------------------
//! @brief Interpolazione sinusoidale smorzata in uscita (y = sin(-13pi/2*(x + 1))* 2^(-10x) + 1)
//! @param p progresso x dell'interpolazione (range 0.0-1.0)
//! @return progresso y dell'interpolazione
float ElasticEaseOut(float p)
{
	return (float)(sin(-13 * (float)M_PI_2 * (p + 1)) * pow(2, -10 * p) + 1);
}
//---------------------------------------------------------------------
//! @brief Interpolazione sinusoidale smorzata in ingresso e uscita ( y = (1/2)*sin(13pi/2*(2*x))* 2 ^(10 * ((2*x) - 1)) in [0, 0.5), y = (1/2)*(sin(-13pi/2*((2x-1)+1))* 2^(-10(2*x-1)) + 2) in [0.5, 1])
//! @param p progresso x dell'interpolazione (range 0.0-1.0)
//! @return progresso y dell'interpolazione
float ElasticEaseInOut(float p)
{
	if (p < 0.5f)
	{
		return (float)(0.5f * sin(13 * (float)M_PI_2 * (2 * p)) * pow(2, 10 * ((2 * p) - 1)));
	}
	else
	{
		return (float)(0.5f * (sin(-13 * (float)M_PI_2 * ((2 * p - 1) + 1)) * pow(2, -10 * (2 * p - 1)) + 2));
	}
}
//---------------------------------------------------------------------
//! @brief Interpolazione cubica sottosmorzata (overshoot) in ingresso ( y = x^3-x*sin(x*pi) )
//! @param p progresso x dell'interpolazione (range 0.0-1.0)
//! @return progresso y dell'interpolazione
float BackEaseIn(float p)
{
	return p * p * p - p * (float)(sin(p * (float)M_PI));
}

float BackEaseInQuadratic(float p)
{
	return p * p - p * (float)(sin(p * (float)M_PI));
}

float LinearBackEaseOut(float p)
{
	float f = (1 - p);
	float ampRimbalzo = 0.75f; //1.0 = half symbol
	return (float)(1 - (f - ampRimbalzo * sin(f * (float)M_PI))); //0.8 ampiezza rimbalzo 
}

//---------------------------------------------------------------------
//! @brief Interpolazione cubica sottosmorzata (overshoot) in uscita ( y = 1-((1-x)^3-(1-x)*sin((1-x)*pi)) )
//! @param p progresso x dell'interpolazione (range 0.0-1.0)
//! @return progresso y dell'interpolazione
float BackEaseOut(float p)
{
	float f = (1 - p);
	return (float)(1 - (f * f * f - f * sin(f * (float)M_PI)));
}
//---------------------------------------------------------------------
//! @brief Interpolazione cubica sottosmorzata (overshoot) in ingresso e uscita ( y = (1/2)*((2x)^3-(2x)*sin(2*x*pi)) in [0, 0.5), y = (1/2)*(1-((1-x)^3-(1-x)*sin((1-x)*pi))+1) in [0.5, 1])
//! @param p progresso x dell'interpolazione (range 0.0-1.0)
//! @return progresso y dell'interpolazione
float BackEaseInOut(float p)
{
	if (p < 0.5f)
	{
		float f = 2 * p;
		return (float)(0.5f * (f * f * f - f * sin(f * (float)M_PI)));
	}
	else
	{
		float f = (1 - (2 * p - 1));
		return (float)(0.5f * (1 - (f * f * f - f * sin(f * (float)M_PI))) + 0.5f);
	}
}
//---------------------------------------------------------------------
//! @brief Interpolazione "rimbalzante" in ingresso
//! @param p progresso x dell'interpolazione (range 0.0-1.0)
//! @return progresso y dell'interpolazione
float BounceEaseIn(float p)
{
	return 1 - BounceEaseOut(1 - p);
}
//---------------------------------------------------------------------
//! @brief Interpolazione "rimbalzante" in uscita
//! @param p progresso x dell'interpolazione (range 0.0-1.0)
//! @return progresso y dell'interpolazione
float BounceEaseOut(float p)
{
	if (p < 4.0f / 11.0f)
	{
		return (121 * p * p) / 16.0f;
	}
	else if (p < 8 / 11.0f)
	{
		return (363 / 40.0f * p * p) - (99 / 10.0f * p) + 17 / 5.0f;
	}
	else if (p < 9 / 10.0f)
	{
		return (4356 / 361.0f * p * p) - (35442 / 1805.0f * p) + 16061 / 1805.0f;
	}
	else
	{
		return (54 / 5.0f * p * p) - (513 / 25.0f * p) + 268 / 25.0f;
	}
}
//---------------------------------------------------------------------
//! @brief Interpolazione "rimbalzante" in ingresso e uscita
//! @param p progresso x dell'interpolazione (range 0.0-1.0)
//! @return progresso y dell'interpolazione
float BounceEaseInOut(float p)
{
	if (p < 0.5f)
	{
		return 0.5f * BounceEaseIn(p * 2);
	}
	else
	{
		return 0.5f * BounceEaseOut(p * 2 - 1) + 0.5f;
	}
}
