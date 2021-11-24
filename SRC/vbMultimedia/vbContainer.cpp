#include "basetypes.h"
#include "vbEngine.h"

void vbContainer::init(WORD width, WORD height)
{
	this->gObjects.owner = this;
	this->changed = TRUE;
	this->scissor = FALSE;
	this->type = TYPE_CONTAINER;
	this->width = width;
	this->height = height;
}
vbContainer::vbContainer(WORD width, WORD height, string name)
{
	this->name = name;
	this->init(width, height);
}

void vbContainer::updateCache()
{
	if (this->useCache == TRUE)
	{
		UnloadTexture(this->canvasCache);
		this->canvasCache.id = 0;
	}
}

void vbContainer::setCacheFlag(BOOL cacheON)
{
	if (cacheON == FALSE)
	{
		UnloadTexture(this->canvasCache);
		this->canvasCache.id = 0;
	}
	this->useCache = cacheON;
}

BOOL vbContainer::getCacheFlag()
{
	return this->useCache;
}

Texture2D vbContainer::getCacheTexture()
{
	return this->canvasCache;
}

vbContainer::~vbContainer()
{
	//TODO deallocate all objects in the list?
}

//vbContainer::vbContainer(vbImageList initvbImageList, WORD width, WORD height, string name)
//{
//	this->init(width, height);
//	this->name = name;
//	//this->images = initvbImageList;
//}
void vbContainer::addObject(vbGraphicObject* ob)
{
	this->addObject(ob, "");
}

void vbContainer::removeObject(vbGraphicObject* ob)
{
	ob->parentCanvas = this;
	ob->parentList = &this->gObjects;
	this->gObjects.removeit(ob);
}
void vbContainer::resize()
{
	Vector2 topleft;
	Vector2 botright;
	for (gObjectIndex it = this->gObjects.begin(); it != this->gObjects.end(); it++)
	{
		if (it == this->gObjects.begin()) 
		{
			topleft = (*it)->position;
			botright.x = (*it)->position.x + (*it)->width;
			botright.y = (*it)->position.y + (*it)->height;
		}
		else
		{
			if ((*it)->position.x < topleft.x) topleft.x = (*it)->position.x;
			if ((*it)->position.y < topleft.y) topleft.y = (*it)->position.y;
			if ((*it)->position.x + (*it)->width > botright.x) botright.x = (*it)->position.x + (*it)->width;
			if ((*it)->position.y + (*it)->height > botright.y) botright.y = (*it)->position.y + (*it)->height;
		}
	}
	this->width = botright.x - topleft.x;
	this->height = botright.y - topleft.y;
}

void vbContainer::addObject(vbGraphicObject* ob, std::string name, WORD layer)
{
	ob->setLayer(layer);
	this->addObject(ob, name);
}

void vbContainer::addObject(vbGraphicObject* ob, std::string name)
{
	ob->parentCanvas = this;
	ob->parentList = &this->gObjects;
	this->gObjects.push_back(ob);
	if (ob->name == "") //if the object is unnamed then I give the one on the list
		ob->name = name;
	if (name == "")
		name = ob->name;
	this->gObjects.goMap[name] = ob;
}

//vbGraphicObject* vbContainer::getObject(const char* sname)
//{
//	if (this->gObjects.goMap.find(sname) != this->gObjects.goMap.end())
//	{
//		if (this->gObjects.goMap[sname]->type == TYPE_CONTAINER)
//			return (vbContainer*)(this->gObjects.goMap[sname]);
//		else if (this->gObjects.goMap[sname]->type == TYPE_TEXTURE)
//			return (vbImage*)(this->gObjects.goMap[sname]);
//		else if (this->gObjects.goMap[sname]->type == TYPE_SEQUENCE)
//			return (vbSequence*)(this->gObjects.goMap[sname]);
//		else if (this->gObjects.goMap[sname]->type == TYPE_TEXT)
//			return (vbTextbox*)(this->gObjects.goMap[sname]);
//		else
//			return (this->gObjects.goMap[sname]);
//	}
//	return (vbGraphicObject*)NULL;
//}