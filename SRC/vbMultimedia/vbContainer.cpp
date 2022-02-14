#include "basetypes.h"
#include "vbEngine.h"

void vbContainer::setup()
{
	vbGraphicObject::setup();
	cacheImage = new vbImage(&this->containerCache);
	cacheImage->isCacheImage = TRUE;
	cacheImage->positioningRule = posRule::POS_CANVAS_RELATIVE;
	this->addObject(this->cacheImage);
}

void vbContainer::update()
{
	vbGraphicObject::update();
	for (vbGraphicObject* obj : this->gObjects)
	{
		if (obj->isAlive && obj->enabled)
			obj->update();
	}
}

void vbContainer::draw()
{
	vbGraphicObject::draw();
	this->inheritedCache = FALSE;
	this->inheritedCachePosition = { 0,0 };

	if ((this->parentContainer == NULL && this->useCache == TRUE) || // if it's the root and needs to ba cached
		(this->parentContainer != NULL && // or not the root and
		this->useCache == TRUE &&	// has to be cached
		this->containerCache.id == NULL && // not yet cached
		this->parentContainer->getCacheTexture().id == NULL)) //and not inside an already cached canvas
	{
			RenderTexture2D targetCache = { 0 };
			targetCache = LoadRenderTexture(this->width, this->height); //create render target
			BeginTextureMode(targetCache);
			ClearBackground(BLANK);  // Clear texture background
			this->inheritedCachePosition = this->transformed.position;
	}
	else
	{
		if (this->parentContainer != NULL && this->parentContainer->getCacheFlag())
		{
			this->inheritedCachePosition = this->parentContainer->inheritedCachePosition;
			inheritedCache = TRUE;
		}
	}

	this->activeArea = this->_calculateActiveArea();
	if (this->inheritedActiveArea || this->useActiveArea)
		BeginScissorMode(this->activeArea.x, this->activeArea.y, this->activeArea.width, this->activeArea.height);

	if (this->containerCache.id == NULL)
	{
		for (vbGraphicObject* obj : this->gObjects)
		{
			if (obj->isAlive && obj->visible)
			{
				if (obj->type == gObjectType::TYPE_CONTAINER && (this->inheritedActiveArea || this->useActiveArea))
					EndScissorMode(); //openGL does not -easily- support nested scissoring, we need to disable it, will be re-enabled inheriting from the parent
				obj->draw();
				if (obj->type == gObjectType::TYPE_CONTAINER && (this->inheritedActiveArea || this->useActiveArea))
					BeginScissorMode(this->activeArea.x, this->activeArea.y, this->activeArea.width, this->activeArea.height);
			}
		}
	}
	else
		this->cacheImage->draw();

	if (this->inheritedActiveArea || this->useActiveArea)
		EndScissorMode();
}

Rectangle vbContainer::_calculateActiveArea()
{
	Rectangle finalScissor = { this->transformed.position.x, this->transformed.position.y, (float)this->transformed.width, (float)this->transformed.height };
	this->inheritedActiveArea = FALSE;
	if (this->parentContainer != NULL)
	{
		auto pc = this->parentContainer;
		if (pc->useActiveArea || pc->inheritedActiveArea)
		{
			this->inheritedActiveArea = TRUE;
			if (pc->activeArea.x > finalScissor.x)
			{
				finalScissor.width -= (pc->activeArea.x - finalScissor.x);
				finalScissor.x = pc->activeArea.x;
			}

			if (pc->activeArea.y > finalScissor.y)
			{
				finalScissor.height -= pc->activeArea.y - finalScissor.y;
				finalScissor.y = pc->activeArea.y;
			}

			if (pc->activeArea.x + pc->activeArea.width < finalScissor.x + finalScissor.width)
				finalScissor.width = (pc->activeArea.x + pc->activeArea.width) - finalScissor.x;
			if (pc->activeArea.y + pc->activeArea.height < finalScissor.y + finalScissor.height)
				finalScissor.height = (pc->activeArea.y + pc->activeArea.height) - finalScissor.y;
		}
	}
	return finalScissor;
}

void vbContainer::init(WORD width, WORD height)
{
	this->gObjects.owner = this;
	this->type = TYPE_CONTAINER;
	this->width = width;
	this->height = height;
}

vbContainer::vbContainer(WORD width, WORD height, string name)
{
	this->name = name;
	this->position = {0,0};
	this->init(width, height);
}

void vbContainer::updateCache()
{
	if (this->useCache == TRUE)
	{
		UnloadTexture(this->containerCache);
		this->containerCache.id = 0;
	}
}

void vbContainer::setCacheFlag(BOOL cacheON)
{
	if (cacheON == FALSE)
	{
		UnloadTexture(this->containerCache);
		this->containerCache.id = 0;
	}
	this->useCache = cacheON;
}

BOOL vbContainer::getCacheFlag()
{
	return (this->useCache || this->inheritedCache);
}

Texture2D vbContainer::getCacheTexture()
{
	return this->containerCache;
}

vbContainer::~vbContainer()
{
	//TODO deallocate all objects in the list?
}


void vbContainer::removeObject(vbGraphicObject* ob)
{
	ob->parentContainer = this;
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

void vbContainer::addObject(vbGraphicObject* ob, std::string name, BOOL applyStyle, WORD layer)
{
	ob->setLayer(layer);
	ob->parentContainer = this;
	ob->parentList = &this->gObjects;
	this->gObjects.push_back(ob);

	if (ob->name == "") //if the object is unnamed then I give the one on the list
		ob->name = name;
	if (name == "")
		name = ob->name;
	ob->setup();
	if (applyStyle)
		ob->applyStyle(pGAME->style(name));
	this->gObjects.goMap[name] = ob;

	if(this->autoResize) this->resize();
}
