#ifndef AH_EASING_H
#define AH_EASING_H

// Se non sono già definite, definizione di pi e pi/2
#ifndef M_PI_2
#define M_PI_2     1.57079632679489661923132169164      //!< valore di Pi/2 
#endif
#ifndef M_PI
#define M_PI       3.14159265358979323846264338328      //!< valore di Pi 
#endif

#define EASE_linear					0	//!< id della funzione di easing lineare		
#define EASE_QuadraticIn			1	//!< id della funzione di easing QuadraticIn	
#define EASE_QuadraticOut			2	//!< id della funzione di easing QuadraticOut	
#define EASE_QuadraticInOut			3	//!< id della funzione di easing QuadraticInOut	
#define EASE_CubicIn				4	//!< id della funzione di easing CubicIn		
#define EASE_CubicOut				5	//!< id della funzione di easing CubicOut		
#define EASE_CubicInOut				6	//!< id della funzione di easing CubicInOut		
#define EASE_QuarticIn				7	//!< id della funzione di easing QuarticIn		
#define EASE_QuarticOut				8	//!< id della funzione di easing QuarticOut		
#define EASE_QuarticInOut			9	//!< id della funzione di easing QuarticInOut	
#define EASE_QuinticIn				10	//!< id della funzione di easing QuinticIn		
#define EASE_QuinticOut				11	//!< id della funzione di easing QuinticOut		
#define EASE_QuinticInOut			12	//!< id della funzione di easing QuinticInOut	
#define EASE_SineIn					13	//!< id della funzione di easing SineIn			
#define EASE_SineOut				14	//!< id della funzione di easing SineOut		
#define EASE_SineInOut				15	//!< id della funzione di easing SineInOut		
#define EASE_CircularIn				16	//!< id della funzione di easing CircularIn		
#define EASE_CircularOut			17	//!< id della funzione di easing CircularOut	
#define EASE_CircularInOut			18	//!< id della funzione di easing CircularInOut	
#define EASE_ExponentialIn			19	//!< id della funzione di easing ExponentialIn	
#define EASE_ExponentialOut			20	//!< id della funzione di easing ExponentialOut	
#define EASE_ExponentialInOut		21	//!< id della funzione di easing ExponentialInOu
#define EASE_ElasticIn				22	//!< id della funzione di easing ElasticIn		
#define EASE_ElasticOut				23	//!< id della funzione di easing ElasticOut		
#define EASE_ElasticInOut			24	//!< id della funzione di easing ElasticInOut	
#define EASE_BackIn					25	//!< id della funzione di easing BackIn			
#define EASE_BackOut				26	//!< id della funzione di easing BackOut		
#define EASE_BackInOut				27	//!< id della funzione di easing BackInOut		
#define EASE_BounceIn				28	//!< id della funzione di easing BounceIn		
#define EASE_BounceOut				29	//!< id della funzione di easing BounceOut		
#define EASE_BounceInOut			30	//!< id della funzione di easing BounceInOut	

//! @brief tipo puntatore a funzione per gli easing
typedef float(*EasingFunction)(float);

// Linear interpolation (no easing)
float LinearInterpolation(float p);

// Quadratic easing; p^2
float QuadraticEaseIn(float p);
float QuadraticEaseOut(float p);
float QuadraticEaseInOut(float p);

// Cubic easing; p^3
float CubicEaseIn(float p);
float CubicEaseOut(float p);
float CubicEaseInOut(float p);

// Quartic easing; p^4
float QuarticEaseIn(float p);
float QuarticEaseOut(float p);
float QuarticEaseInOut(float p);

// Quintic easing; p^5
float QuinticEaseIn(float p);
float QuinticEaseOut(float p);
float QuinticEaseInOut(float p);

// Sine wave easing; sin(p * PI/2)
float SineEaseIn(float p);
float SineEaseOut(float p);
float SineEaseInOut(float p);

// Circular easing; sqrt(1 - p^2)
float CircularEaseIn(float p);
float CircularEaseOut(float p);
float CircularEaseInOut(float p);

// Exponential easing, base 2
float ExponentialEaseIn(float p);
float ExponentialEaseOut(float p);
float ExponentialEaseInOut(float p);

// Exponentially-damped sine wave easing
float ElasticEaseIn(float p);
float ElasticEaseOut(float p);
float ElasticEaseInOut(float p);

// Overshooting cubic easing; 
float BackEaseIn(float p);
float BackEaseInQuadratic(float p);
float LinearBackEaseOut(float p);
float BackEaseOut(float p);
float BackEaseOutQuadratic(float p);
float BackEaseInOut(float p);

// Exponentially-decaying bounce easing
float BounceEaseIn(float p);
float BounceEaseOut(float p);
float BounceEaseInOut(float p);

//! @brief array contenente puntatori a tutte le funzioni di easing
static const EasingFunction EASING_CALC[31] =
{
	LinearInterpolation,
	QuadraticEaseIn,
	QuadraticEaseOut,
	QuadraticEaseInOut,
	CubicEaseIn,
	CubicEaseOut,
	CubicEaseInOut,
	QuarticEaseIn,
	QuarticEaseOut,
	QuarticEaseInOut,
	QuinticEaseIn,
	QuinticEaseOut,
	QuinticEaseInOut,
	SineEaseIn,
	SineEaseOut,
	SineEaseInOut,
	CircularEaseIn,
	CircularEaseOut,
	CircularEaseInOut,
	ExponentialEaseIn,
	ExponentialEaseOut,
	ExponentialEaseInOut,
	ElasticEaseIn,
	ElasticEaseOut,
	ElasticEaseInOut,
	BackEaseIn,
	BackEaseOut,
	BackEaseInOut,
	BounceEaseIn,
	BounceEaseOut,
	BounceEaseInOut
};

#endif
