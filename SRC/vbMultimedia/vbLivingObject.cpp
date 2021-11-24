#include "vbEngine.h"

vbData* pDATA = NULL;
vbGame* pGAME = NULL;

vbLivingObject::vbLivingObject(vbGame* game, vbData* data)
{
	this->DATA = data;
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