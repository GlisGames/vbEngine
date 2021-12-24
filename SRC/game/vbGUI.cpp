#include "vbEngine.h"
vbGUI* vbGUI::instance = NULL; //Initialization here, otherwise the compiler ignore this, leading to linker error

vbGUI::vbGUI()
{
	this->isAlive = TRUE;
}

void vbGUI::render()
{

}

void vbGUI::update()
{

}