#include "DeveloperInfoObject.h"

DeveloperInfoObject::DeveloperInfoObject()
{
	this->rect = { 0.0f, 0.0f, 36.0f, 36.0f };
}

DeveloperInfoObject::~DeveloperInfoObject()
{
}


void DeveloperInfoObject::update()
{
	if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(GetMousePosition(), this->rect))
	{
#ifdef PLATFORM_WEB
		emscripten_run_script("console.log('Developed by Glis Games (www.glisgames.com) for NEXT Digital. Made in Vietnam \\uD83C\\uDDFB\\uD83C\\uDDF3')");
#else
		std::cout << "Developed by Glis Games (www.glisgames.com) for NEXT Digital. Made in Vietnam" << std::endl;
#endif // PLATFORM_WEB

	}
}

void DeveloperInfoObject::render()
{
	//DrawRectangleRec(this->rect, RED);
}
