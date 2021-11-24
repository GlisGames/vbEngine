#ifndef vbImage_H
#define vbImage_H

#include "basetypes.h"
#include "vbGraphicObject.h"

class vbImage : public vbGraphicObject
{
private:
	void init_(WORD layer);
protected:
	Texture2D *texture = NULL;
public:
	vbImage(WORD layer = 0);
	vbImage(Texture2D* tex, Vector2 pos = {0,0}, std::string name = "", WORD layer = 0);
	void setTexture(Texture2D* tex);
	Texture2D *getTexture();
	~vbImage();
};

typedef std::list<vbImage*> vbImageList;
typedef vbImageList::iterator ivbImage;

#endif