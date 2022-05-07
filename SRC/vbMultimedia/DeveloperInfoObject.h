#ifndef EASTER_EGG_OBJECT_H
#define EASTER_EGG_OBJECT_H

#include "vbEngine.h"
#ifdef PLATFORM_WEB
#include <emscripten/emscripten.h>
#include <emscripten/html5.h>
#else
#include <iostream>
#endif // PLATFORM_WEB

class DeveloperInfoObject
{
public:
	DeveloperInfoObject();
	~DeveloperInfoObject();
	Rectangle rect = {0.0f, 0.0f, 36.0f, 36.0f};

	void update();
	void render();
	
};


#endif // !EASTER_EGG_OBJECT_H
