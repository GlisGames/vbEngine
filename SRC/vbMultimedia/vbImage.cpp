#include "vbEngine.h"
#include "vbImage.h"

void vbImage::init_(WORD layer)
{
	this->type = TYPE_TEXTURE;
	this->setLayer(layer);
}

vbImage::~vbImage()
{ 
	//se fa parte di una lista lo vado a rimuovere
	if (this->parentList)
		this->parentList->removeit(this);
}

vbImage::vbImage(WORD layer)
{
	this->name = "";
	if(this->texture)
		this->texture->id = -1;
	this->init_(layer);
}

vbImage::vbImage(Texture2D* tex,  Vector2 pos, std::string name, WORD layer)
{
	this->init_(layer);
	this->setTexture(tex);
	this->name = name;
	this->position = pos;
}

void vbImage::setTexture(Texture2D* tex)
{
	this->texture = tex;
	if (tex != NULL)
	{
		this->width = tex->width;
		this->height = tex->height;
	}
}

Texture2D* vbImage::getTexture()
{
	return this->texture;
}