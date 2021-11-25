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
	bool useCache = FALSE;
public:
	//vbImageList images;
	//canvasList canvases;
	Texture2D canvasCache = { 0 };
	gObjectList gObjects;
	BOOL changed = TRUE;
	BOOL scissor = FALSE;
	Rectangle scissorBox;
	vbContainer(WORD width = 1, WORD height = 1, std::string name = "");
	~vbContainer();
	//vbContainer(vbImageList initvbImageList, WORD width = 0, WORD height = 0, std::string name = "");
	Texture2D getCacheTexture();
	void setCacheFlag(BOOL cacheON);
	void updateCache();
	BOOL getCacheFlag();
	void addObject(vbGraphicObject* ob, std::string name = "", BOOL applyStyle = TRUE, WORD layer = 0);
	void removeObject(vbGraphicObject* ob);
	void resize();
	//vbGraphicObject* getObject(const char* sname);

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