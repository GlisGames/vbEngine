#include "vbEngine.h"

vbGame* pGAME = NULL;

vbLivingObject::vbLivingObject()
{
	this->init();
	this->initialized = TRUE;
}

//vbLivingObject::vbLivingObject()
//{
//}

vbLivingObject::~vbLivingObject()
{
}