#ifndef VBGRAPHICOBJECT_H
#define VBGRAPHICOBJECT_H

#include "basetypes.h"
#include "vbLivingObject.h"
#include "vbTween.h"

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
class styleElement;

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

class vbProperties
{
	public:
	float scale = 1.0f;
	float rotation = 0.0f;
	Vector2 position = { 0,0 };
	WORD width = 0;
	WORD height = 0;
	Color colour = WHITE;
	BOOL visible = TRUE;
	BOOL canBeClicked = TRUE;
};

class vbGraphicObject: public vbGameObject, public vbProperties
{
private:
	Vector2 _calculateAbsolutePosition();
	// Layers get printed from the smallest to the highest
	// means that layer 0 is printer on the back of layer 1
	// layer with the highest value gets printed on top
	// NOTE: 
	// The draw() function gets called from the smalles layer to the highest
	// The update() function gets called from the highest to the smallest
	int layer = 0; 
	BOOL _isClicked = FALSE;
public:
	vbGraphicObject();
	~vbGraphicObject();

	vbProperties transformed;

	virtual void setup();

	virtual void update();

	virtual void draw();

	//properties transformed;
	void sendToBack();
	void moveToFront();
	void sendBackwards();
	void moveForward();
	void setLayer(WORD l);
	void applyStyle(styleElement* prop);
	vbTweenMap tweens;
	vbTween* addtween(const char* name, vbTween tw) { return this->tweens.addtween(name, tw); };
	std::string name;
	Vector2 getAbsolutePosition();
	WORD getLayer();
	BOOL inheritTransformations = TRUE;
	Vector2 pivot = { 0,0 };
	BOOL useCenterCoordinates = FALSE; //the printing coordinates are refered to the center of the image rather than the top left
	posRule positioningRule = posRule::POS_ABSOLUTE;
	transformRegRule regPointRule = transformRegRule::REG_CENTER;


	Color fallbackColour = WHITE; //colour to be restored in case of changes
	BOOL debugBox = FALSE;
	gObjectType type = TYPE_NONE;
	gObjectList *parentList = NULL;
	class vbContainer* parentContainer = NULL; //forward declaration
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
};

#endif // !VBGRAPHICOBJECT_H