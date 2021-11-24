#pragma once
#include "basetypes.h"
#include "vbLivingObject.h"
#include "vbTween.h"
//#include "vbContainer.h"

enum gObjectType
{
	TYPE_NONE = 0,
	TYPE_TEXTURE = 0x1,
	TYPE_CONTAINER = 0x2,
	TYPE_SEQUENCE = 0x4,
	TYPE_TEXT = 0x8,
	TYPE_LIVING_OBJECT = 0x10,
//	TYPE_TEXT_ALFONS = 0x20,
};

enum class posRule
{
	POS_ABSOLUTE = 0,
	POS_CANVAS_RELATIVE = 1,
	POS_PIVOT_RELATIVE = 2
};

enum class transformRegRule
{
	REG_TOP_LEFT = 0,
	REG_CENTER = 1,
	REG_POINT = 2
};

class vbContainer;
class vbGraphicObject;

class gObjectList : public std::list<vbGraphicObject*> //std::map<std::string, vbGraphicObject*>
{
private:
public:
	gObjectList()
	{
		this->owner = NULL;
	}
	BOOL toSort = TRUE;
	std::map<std::string, vbGraphicObject*> goMap;
	vbContainer* owner = NULL;
	gObjectList::iterator findit(vbGraphicObject* o);
	void removeit(vbGraphicObject* o);
	void sortMe();
};
typedef gObjectList::iterator gObjectIndex;

class vbGraphicObject: public vbLivingObject
{
private:
	int layer = 0;
	BOOL _isClicked = FALSE;
public:
	vbGraphicObject();
	~vbGraphicObject();
	void sendToBack();
	void moveToFront();
	void sendBackwards();
	void moveForward();
	void setLayer(WORD l);
	vbTweenMap tweens;
	vbTween* addtween(const char* name, vbTween tw) { return this->tweens.addtween(name, tw); };
	std::string name;
	Vector2 getAbsolutePosition();
	WORD getLayer();
	FLOAT zoom = 1.0f; //zoom % - 100% is the original size
	int rotation = 0;
	Vector2 position = { 0,0 };
	Vector2 pivot = { 0,0 };
	BOOL useCenterCoordinates = FALSE; //the printing coordinates are refered to the center of the image rather than the top left
	posRule positioningRule = posRule::POS_ABSOLUTE;
	transformRegRule regPointRule = transformRegRule::REG_CENTER;
	WORD width = 0;
	WORD height = 0;
	Color colour = WHITE;
	Color fallbackColour = WHITE; //colour to be restored in case of changes
	BOOL visible = TRUE;
	BOOL debugBox = FALSE;
	gObjectType type = TYPE_NONE;
	gObjectList *parentList = NULL;
	class vbContainer* parentCanvas = NULL; //forward declaration
	void setParams(Vector2 position, WORD rotation, BYTE zoom, Color tint);

	bool operator < (const vbGraphicObject& str) const
	{
		return (layer < str.layer);
	}
	bool operator > (const vbGraphicObject& str) const
	{
		return (layer > str.layer);
	}
	bool operator < (const vbGraphicObject* str) const
	{
		return (layer < str->layer);
	}
	bool operator > (const vbGraphicObject* str) const
	{
		return (layer > str->layer);
	}
	struct minLayer
	{
		inline bool operator() (const vbGraphicObject* s1, const vbGraphicObject* s2)
		{
			return ((s1->layer) > s2->layer);
		}
	};
	void setClick(BOOL on)
	{
		this->_isClicked = on;
	}
	BOOL isClickable = FALSE;
	BOOL isClicked();
	BOOL isMouseOver();
	vbGraphicObject* getChild(const char* sname);
	vbGraphicObject* getObject(const char* sname);
	//template <typename T>
	//T* getObject(const char* sname);
	//{
	//	if (this->type == TYPE_CONTAINER)
	//	{
	//		vbContainer* cv = (vbContainer*)(this);
	//		if (cv->gObjects.goMap.find(sname) != cv->gObjects.goMap.end())
	//		{
	//			return (T*)(cv->gObjects.goMap[sname]);
	//		}
	//	}
	//	return (T*)NULL; //TODO gestire errore
	//};


	//{
	//	if (this->gObjects.goMap.find(sname) != this->gObjects.goMap.end())
	//	{
	//		return (T*)(this->gObjects.goMap[sname]);
	//	}
	//	return (T*)NULL;
	//}
};


