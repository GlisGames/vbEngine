#ifndef EASTER_EGG_OBJECT_H
#define EASTER_EGG_OBJECT_H

#include "vbEngine.h"
#ifdef PLATFORM_WEB
#include <emscripten/emscripten.h>
#include <emscripten/html5.h>
#else
#include <iostream>
#endif // PLATFORM_WEB

class EasterEggObject
{
public:
	EasterEggObject();
	~EasterEggObject();
	Vector2 center = {18.0f, 18.0f};
	float radius = 18.0f;

	void update();
	void render();
	
};


#endif // !EASTER_EGG_OBJECT_H
