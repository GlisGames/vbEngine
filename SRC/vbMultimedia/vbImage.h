#ifndef vbImage_H
#define vbImage_H

#include "basetypes.h"
#include "vbGraphicObject.h"
#include "vbTexture.h"

class vbImage : public vbGraphicObject
{
private:
	void init_(WORD layer);
protected:
	Texture2D *texture = NULL;
	vbSpriteTexture *spriteTexture = NULL;
	BOOL isSpriteTexture = FALSE;
public:
	vbImage(WORD layer = 0);
	vbImage(Texture2D* tex, Vector2 pos = {0,0}, std::string name = "", WORD layer = 0);
	vbImage(vbSpriteTexture* tex, Vector2 pos = {0,0}, std::string name = "", WORD layer = 0);

	virtual void setup();
	virtual void update();
	virtual void draw();
	BOOL isCacheImage = FALSE;
	void setTexture(Texture2D* tex);
	void setTexture(vbSpriteTexture* tex);
	Texture2D *getTexture();
	vbSpriteTexture *getSpriteTexture();
	~vbImage();
};

typedef std::list<vbImage*> vbImageList;
typedef vbImageList::iterator ivbImage;

// vbImageMap
class vbImageMap : private std::map<std::string, vbSpriteTexture>
{
public:
	void addTexture(std::string texname, vbSpriteTexture tex);
	vbSpriteTexture* getTexturePtr(std::string str, BOOL searchOnly = FALSE);
	vbSpriteTexture* operator [](std::string str);
};

#endif