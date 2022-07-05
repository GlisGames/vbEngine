#include "vbEngine.h"

vbGraphicObject::~vbGraphicObject()
{
	this->tweens.clear();
	//if(this->parentList)
	//	this->parentList->removeit(this);
}

void vbGraphicObject::setup()
{
	vbGameObject::setup();
}

void vbGraphicObject::update()
{
	vbGameObject::update();
	this->tweens.stepAll();

	this->transformed.position = _calculateAbsolutePosition();
	if (this->parentContainer != NULL && this->inheritTransformations == TRUE)
	{
		this->transformed.scale = this->scale * this->parentContainer->transformed.scale;
		this->transformed.rotation = this->rotation + this->parentContainer->transformed.rotation;

		if (this->parentContainer->colour.a != 255 || this->parentContainer->colour.r != 255 ||
			this->parentContainer->colour.g != 255 || this->parentContainer->colour.b != 255)
			this->transformed.colour = colorApplyFilter(this->colour, this->parentContainer->colour);
		else
			this->transformed.colour = this->colour;

		this->transformed.width = this->width * this->transformed.scale;
		this->transformed.height = this->height * this->transformed.scale;

		this->transformed.visible = this->parentContainer->transformed.visible;
		if (this->regPointRule == transformRegRule::REG_CENTER && (this->parentContainer->transformed.scale != this->transformed.scale || this->parentContainer->regPointRule == transformRegRule::REG_TOP_LEFT))
		{
			this->transformed.position =
			{ this->transformed.position.x + (((float)this->width * 0.5f) * (1.0f - this->transformed.scale))
			, this->transformed.position.y + (((float)this->height * 0.5f) * (1.0f - this->transformed.scale)) };
		}
	}
}


void vbGraphicObject::draw()
{
	vbGameObject::draw();
	

	if (this->debugBox == TRUE)
		DrawRectangleLinesEx({ this->transformed.position.x, this->transformed.position.y, (float)this->transformed.width, (float)this->transformed.height }, 1, RED);
}

vbGraphicObject::vbGraphicObject()
{
	this->position.x	= 0;
	this->position.y	= 0;
	this->colour		= WHITE;
	this->visible		= TRUE;
	this->scale			= 1.0f;
	this->rotation		= 0;

	this->parentList	= NULL;
	this->layer			= 0;
}

void vbGraphicObject::setParams(Vector2 position, WORD rotation, BYTE zoom, Color tint)
{
	this->position = position;
	this->colour = tint;
	this->scale = zoom;
	this->rotation = rotation;
}

void vbGraphicObject::sendToBack()
{
	if (this->parentList != NULL)
	{
		this->layer = (*this->parentList).front()->layer + 1;
		this->parentList->toSort = TRUE;
		//this->parentList->splice(this->parentList->begin(), *this->parentList, this->parentList->findit(this));
	}
}
void vbGraphicObject::moveToFront()
{
	if (this->parentList != NULL)
	{
		this->layer = (*this->parentList).back()->layer - 1;
		this->parentList->toSort = TRUE;
		//this->parentList->splice(this->parentList->end(), *this->parentList, this->parentList->findit(this));
	}
}
void vbGraphicObject::sendBackwards()
{
	if (this->parentList != NULL)
	{	//serious iterators magic happens down here
		auto source = this->parentList->findit(this);
		if (*source != this->parentList->front())
		{
			auto dest = source;
			dest--;
			vbGraphicObject* pdest = *dest;
			int destlayer = (*dest)->layer;
			*dest = *source;
			(*source)->layer = destlayer;
			*source = pdest;
		}
	}
}
void vbGraphicObject::moveForward()
{
	if (this->parentList != NULL)
	{	//serious iterators magic happens down here
		auto source = this->parentList->findit(this);
		if (*source != this->parentList->back())
		{
			auto dest = source;
			dest++;
			vbGraphicObject* pdest = *dest;
			int destlayer = (*dest)->layer;
			*dest = *source;
			(*source)->layer = destlayer;
			*source = pdest;
		}
	}
}
void vbGraphicObject::applyStyle(styleElement* prop)
{
	if (prop != NULL)
	{
		if (prop->position != NULL)
		{
			this->position.x = prop->position->x;
			this->position.y = prop->position->y;
		}
		if (prop->size != NULL)
		{
			this->width = prop->size->x;
			this->height = prop->size->y;
		}
		if (prop->texture != NULL && this->type == TYPE_TEXTURE)
		{
			vbImage* tx;
			tx = (vbImage*)(this);
			tx->setTexture(prop->texture);
		}
		if (prop->fontName != NULL && this->type == TYPE_TEXT)
		{
			vbTextbox* tb;
			tb = (vbTextbox*)this;
			tb->setFont(prop->fontName);
		}
		if (prop->scale != NULL)
		{
			this->scale = prop->scale;
		}
	}
}

void vbGraphicObject::setLayer(WORD l)
{
	if (this->layer != l)
	{
		this->layer = l;
		if (this->parentList != NULL)
			this->parentList->toSort = TRUE;
	}
}

BOOL vbGraphicObject::isClicked()
{
	if (this->enabled == FALSE)
		return false;

	return _isClicked;
	//if (IsMouseButtonPressed(0))
	//	return isMouseOver();
	//return false;
}

BOOL vbGraphicObject::isMouseDown()
{
	if (this->enabled == FALSE)
		return false;

	return _isMouseDown;
}

BOOL vbGraphicObject::isMouseOver()
{
//	Vector2 windowSize = { (float)window_getInnerWidth(), (float)window_getInnerHeight() };
//#ifdef PLATFORM_WEB
//	Vector2 ratio = { windowSize.x / (float)GetScreenWidth(), windowSize.y / (float)GetScreenHeight() };
//#else
//	Vector2 ratio = { 1,1 };
//#endif // PLATFORM_WEB
//	Vector2 ret = GetMousePosition();
//	ret.x /= ratio.x;
//	ret.y /= ratio.y;
//	Vector2 absPos = this->getAbsolutePosition();
//	if (ret.x >= absPos.x && ret.x <= (absPos.x + (this->width/ratio.x)) && ret.y >= absPos.y && ret.y <= (absPos.y + (this->height/ratio.y)))
//		return true;

	Vector2 ret = GetMousePosition();
	Vector2 absPos = this->transformed.position;
	if (ret.x >= absPos.x && ret.x <= (absPos.x + this->transformed.width) && ret.y >= absPos.y && ret.y <= (absPos.y + this->transformed.height))
		return true;
	return false;
}



WORD vbGraphicObject::getLayer()
{
	return this->layer;
}

Vector2 vbGraphicObject::getAbsolutePosition()
{
	Vector2 pos = { 0, 0 };
	//Calculate the right position according to the positioning role
	if (this->positioningRule == posRule::POS_ABSOLUTE)
		pos = this->position;
	else if (this->positioningRule == posRule::POS_PIVOT_RELATIVE)
	{
		pos.x = this->position.x + this->pivot.x;
		pos.y = this->position.y + this->pivot.y;
	}
	else if (this->positioningRule == posRule::POS_CANVAS_RELATIVE)
	{
		vbContainer* pc = this->parentContainer;
		if (pc == NULL)
			pos = this->position;
		else
		{
			Vector2 parentPos = pc->getAbsolutePosition();
			pos.x = this->position.x + parentPos.x;
			pos.y = this->position.y + parentPos.y;
		}
	}
	else
		pos = this->position;

	if (this->useCenterCoordinates == TRUE)
	{
		pos.x = this->position.x - (this->width / 2);
		pos.y = this->position.y - (this->height / 2);
	}
	return pos;
}

Vector2 vbGraphicObject::_calculateAbsolutePosition()
{
	Vector2 pos = { 0, 0 };
	//Calculate the right position according to the positioning role
	if (this->positioningRule == posRule::POS_ABSOLUTE)
		pos = this->position;
	else if (this->positioningRule == posRule::POS_PIVOT_RELATIVE)
	{
		pos.x = this->position.x + this->pivot.x;
		pos.y = this->position.y + this->pivot.y;
	}
	else if (this->positioningRule == posRule::POS_CANVAS_RELATIVE)
	{
		vbContainer* pc = this->parentContainer;
		if (pc == NULL)
			pos = this->position;
		else
		{
			Vector2 parentPos = pc->transformed.position;
			pos.x = this->position.x + parentPos.x;
			pos.y = this->position.y + parentPos.y;
		}
	}
	else
		pos = this->position;

	if (this->useCenterCoordinates == TRUE)
	{
		pos.x = this->position.x - (this->width / 2);
		pos.y = this->position.y - (this->height / 2);
	}
	return pos;
}

vbGraphicObject* vbGraphicObject::getChild(const char* sname)
{
	if (this->type == TYPE_CONTAINER)
	{
		vbContainer* ref = (vbContainer*)this;
		if (ref->gObjects.goMap.find(sname) != ref->gObjects.goMap.end())
		{
			if (ref->gObjects.goMap[sname]->type == TYPE_CONTAINER)
				return (vbContainer*)(ref->gObjects.goMap[sname]);
			else if (ref->gObjects.goMap[sname]->type == TYPE_TEXTURE)
				return (vbImage*)(ref->gObjects.goMap[sname]);
			else if (ref->gObjects.goMap[sname]->type == TYPE_SEQUENCE)
				return (vbSequence*)(ref->gObjects.goMap[sname]);
			else if (ref->gObjects.goMap[sname]->type == TYPE_TEXT)
				return (vbTextbox*)(ref->gObjects.goMap[sname]);
			else
				return (ref->gObjects.goMap[sname]);
		}
	}
	return (vbGraphicObject*)NULL;
}

void gObjectList::sortMe()
{
	if (this->toSort == TRUE)
	{
		std::sort(this->begin(), this->end(), vbGraphicObject::minLayer());
		//this->sort(vbGraphicObject::minLayer());
		this->toSort = FALSE;
	}
}

void gObjectList::removeit(vbGraphicObject* o)
{
	gObjectIndex it = this->findit(o);
	if(it != this->end())
		this->erase(it);
}

gObjectList::iterator gObjectList::findit(vbGraphicObject* o)
{
	gObjectIndex it = std::find(this->begin(), this->end(), o);
	return it;
}

vbGraphicObject* vbGraphicObject::getObject(const char* sname)
{
	if (this->type == TYPE_CONTAINER)
	{
		vbContainer* cv = (vbContainer*)(this);
		if (cv->gObjects.goMap.find(sname) != cv->gObjects.goMap.end())
		{
			return (vbGraphicObject*)(cv->gObjects.goMap[sname]);
		}
	}
	return NULL; //TODO gestire errore
};