#include "EasterEggObject.h"

EasterEggObject::EasterEggObject()
{
	this->center.x = 18.0f;
	this->center.y = 18.0f;
	this->radius = 18.0f;
}

EasterEggObject::~EasterEggObject()
{
}


void EasterEggObject::update()
{
	if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionPointCircle(GetMousePosition(), this->center, this->radius))
	{
#ifdef PLATFORM_WEB
		emscripten_run_script("console.log('Developed by Glis Games (www.glisgames.com) for NEXT Digital. Made in Vietnam \\uD83C\\uDDFB\\uD83C\\uDDF3')");
#else
		std::cout << "Developed by Glis Games (www.glisgames.com) for NEXT Digital. Made in Vietnam" << std::endl;
#endif // PLATFORM_WEB

	}
}

void EasterEggObject::render()
{
	//DrawCircleV(this->center, this->radius, RED);
}
