#include "vbEngine.h"

vbGame* pGAME = NULL;

vbGameObject::vbGameObject()
{
	this->setup();
	this->initialized = TRUE;
}

vbGameObject::~vbGameObject()
{
}