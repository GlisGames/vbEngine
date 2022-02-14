#include "vbEngine.h"
#include "vbImage.h"

void vbImage::init_(WORD layer)
{
	this->type = TYPE_TEXTURE;
	this->setLayer(layer);
}

vbImage::~vbImage()
{ 
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

void vbImage::update()
{
	vbGraphicObject::update();

}

void vbImage::setup()
{
	vbGraphicObject::setup();

}

void vbImage::draw()
{
	vbGraphicObject::draw();
	if (this->getTexture() != NULL)
	{
		Vector2 origin = { 0,0 };
		if (this->transformed.rotation != 0)
		{	// here we change the point of origin so that the rotation point is centered, look inside 'DrawTexturePro' to know why
			origin = { ((float)this->transformed.width / 2.0f), ((float)this->transformed.height / 2.0f)};
			this->transformed.position.x += (float)this->transformed.width / 2.0f;
			this->transformed.position.y += (float)this->transformed.height / 2.0f;
		}
		
		Rectangle source = { 0.0f, 0.0f, (float)this->width, (float)this->height }; // Piece of the texture to print (all of it)
		Rectangle dest = { //portion of the framebuffer to draw with the target texture
			this->transformed.position.x, 
			this->transformed.position.y, 
			(float)this->transformed.width, 
			(float)this->transformed.height };

		//DrawTextureEx(*this->getTexture(), this->transformed.position, this->transformed.rotation, this->transformed.scale, this->transformed.colour);
		
		if (isCacheImage) //cached containers created via render target are vertically flipped for openGL reasons...
			source.height *= -1;

		DrawTexturePro(*this->getTexture(), source, dest, origin, this->transformed.rotation, this->transformed.colour);

		if (this->debugBox == TRUE)
			DrawRectangleLinesEx(dest, 1, RED);
	}
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

// vbImageMap
void vbImageMap::addTexture(std::string texname, Texture2D tex)
{
	this->insert(std::pair<std::string, Texture2D>(texname, tex));
}

Texture2D* vbImageMap::getTexturePtr(std::string str)
{
	std::transform(str.begin(), str.end(), str.begin(), ::toupper);
	vbImageMap::iterator it = this->find(str);
	if (it != this->end())
		return &this->at(str);
	else
	{
		string msg = "TEXTURE '" + str + "' NOT FOUND";
		PANIC(msg.c_str());
		return NULL;
	}
}

Texture2D* vbImageMap::operator [](std::string str)
{
	return getTexturePtr(str);
}
