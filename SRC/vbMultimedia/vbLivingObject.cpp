#include "vbEngine.h"

vbGame* pGAME = NULL;

vbLivingObject::vbLivingObject(vbGame* game)
{
	this->GAME = game;
	//this->type = TYPE_LIVING_OBJECT;
	//GAME->livingObjects.push_front(this);
	this->init();
	this->initialized = TRUE;
}
//vbLivingObject::vbLivingObject()
//{ 
//	this->type = TYPE_LIVING_OBJECT; 
//}

vbLivingObject::~vbLivingObject()
{
	//if(this->GAME)
	//	this->GAME->livingObjects.remove(this);
}