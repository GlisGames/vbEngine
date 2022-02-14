#ifndef VBCONTAINER_H
#define VBCONTAINER_H

#include <list>
#include "vbEngine.h"
#include "basetypes.h"
#include "vbGraphicObject.h"
#include "vbImage.h"
class vbContainer;

typedef std::list<vbContainer*> canvasList;
typedef std::list<vbContainer*>::iterator ivbCanvas;

class vbContainer : public vbGraphicObject
{
private:
	void init(WORD width, WORD height);
	Rectangle _calculateActiveArea();
	bool useCache = FALSE;
public:
	Texture2D containerCache = { 0 };
	vbImage *cacheImage = NULL;
	gObjectList gObjects;
	BOOL autoResize = FALSE;

	vbContainer(WORD width = 1, WORD height = 1, std::string name = "");
	~vbContainer();
	BOOL useActiveArea = FALSE;
	BOOL inheritedActiveArea = FALSE;
	BOOL inheritedCache = FALSE;
	Vector2 inheritedCachePosition = { 0,0 };
	Rectangle activeArea = Rectangle({ 0,0,0,0 });
	Texture2D getCacheTexture();
	void setCacheFlag(BOOL cacheON);
	void updateCache();
	BOOL getCacheFlag();
	void addObject(vbGraphicObject* ob, std::string name = "", BOOL applyStyle = TRUE, WORD layer = 0);
	void removeObject(vbGraphicObject* ob);
	void resize();

	virtual void vbContainer::setup();
	virtual void vbContainer::update();
	virtual void vbContainer::draw();

	vbContainer* getChildCanvas(const char* sname)
	{
		if (this->gObjects.goMap.find(sname) != this->gObjects.goMap.end())
		{
			if (this->gObjects.goMap[sname]->type == TYPE_CONTAINER)
				return (vbContainer*)(this->gObjects.goMap[sname]);
		}
		return NULL;
	}
	vbGraphicObject* operator[] (const char* sname)
	{
		return this->getChild(sname);
	}

	//~vbContainer();
};

#endif