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

vbImage::vbImage(Texture2D* tex, Vector2 pos, std::string name, WORD layer)
{
	this->init_(layer);
	this->setTexture(tex);
	this->name = name;
	this->position = pos;
}

vbImage::vbImage(vbSpriteTexture* tex, Vector2 pos, std::string name, WORD layer)
{
	this->init_(layer);
	this->setTexture(tex);
	this->name = name;
	this->position = pos;
}

void vbImage::update()
{
	vbGraphicObject::update();
	if (this->getTexture() != NULL)
	{
		if (this->transformed.rotation != 0)
		{	// here we change the point of origin so that the rotation point is centered, look inside 'DrawTexturePro' to know why
			this->transformed.position.x += (float)this->transformed.width / 2.0f;
			this->transformed.position.y += (float)this->transformed.height / 2.0f;
		}
	}
}

void vbImage::setup()
{
	vbGraphicObject::setup();

}

void vbImage::draw()
{
	vbGraphicObject::draw();
	

	if ((!this->isSpriteTexture && this->getTexture() != NULL) || (this->isSpriteTexture && this->getSpriteTexture() != NULL))
	{
		Vector2 origin = { 0,0 };
		if (this->transformed.rotation != 0)
		{	// here we change the point of origin so that the rotation point is centered, look inside 'DrawTexturePro' to know why
			if(this->isSpriteTexture)
				origin = { (this->spriteTexture->originalcut.width / 2.0f), (this->spriteTexture->originalcut.height / 2.0f) };
			else
				origin = { ((float)this->transformed.width / 2.0f), ((float)this->transformed.height / 2.0f)};
			this->transformed.position.x += origin.x;
			this->transformed.position.y += origin.y;
		}
		
		Rectangle source;
		if(this->isSpriteTexture == FALSE)
			source = { 0.0f, 0.0f, (float)this->width, (float)this->height }; // Piece of the texture to print (all of it)
		else
			source = { 
			this->spriteTexture->spriteFrame.x, this->spriteTexture->spriteFrame.y,
			this->spriteTexture->spriteFrame.width, this->spriteTexture->spriteFrame.height
		};

		Rectangle dest;
		if(this->isSpriteTexture == FALSE)
			dest = { //portion of the framebuffer to draw with the target texture
				this->transformed.position.x,
				this->transformed.position.y,
				(float)this->transformed.width,
				(float)this->transformed.height
			};
		else
		{
			FLOAT ratiow = this->spriteTexture->originalcut.width / (float)this->spriteTexture->originalSize.x;
			FLOAT ratioh = this->spriteTexture->originalcut.height / (float)this->spriteTexture->originalSize.y;
			//FLOAT scaledratiow = (float)this->transformed.width / this->spriteTexture->originalcut.width;
			//FLOAT scaledratioh = (float)this->transformed.height / this->spriteTexture->originalcut.height;
			dest = {
				this->transformed.position.x + (this->spriteTexture->originalcut.x * this->transformed.scale),
				this->transformed.position.y + (this->spriteTexture->originalcut.y * this->transformed.scale),
				((float)this->transformed.width * ratiow),
				((float)this->transformed.height * ratioh)
			};
		}

		if (isCacheImage) 
			source.height *= -1; // Cached containers created via render target are vertically flipped for openGL reasons...
		else
		{
			// When caching, hence inside a render target, the coordinate system is relative to the coordinates of the parent container
			dest.x -= this->parentContainer->inheritedCachePosition.x;
			dest.y -= this->parentContainer->inheritedCachePosition.y;
		}

		if (this->isSpriteTexture == FALSE)
			DrawTexturePro(*this->getTexture(), source, dest, origin, this->transformed.rotation, this->transformed.colour);
		else
			DrawTexturePro(pGAME->spriteSheets[this->spriteTexture->spriteID], source, dest, origin, this->transformed.rotation, this->transformed.colour);

		if (this->debugBox == TRUE)
			DrawRectangleLinesEx(dest, 2, RED);
	}
}

void vbImage::setTexture(Texture2D* tex)
{
	this->texture = tex;
	if (tex != NULL)
	{
		this->width = tex->width;
		this->height = tex->height;
		isSpriteTexture = FALSE;
	}
}

void vbImage::setTexture(vbSpriteTexture* tex)
{
	this->spriteTexture = tex;
	if (tex != NULL)
	{
		this->width = tex->originalSize.x;
		this->height = tex->originalSize.y;
		isSpriteTexture = TRUE;
	}
}

Texture2D* vbImage::getTexture()
{
	return this->texture;
}

vbSpriteTexture* vbImage::getSpriteTexture()
{
	return this->spriteTexture;
}

// vbImageMap
void vbImageMap::addTexture(std::string texname, vbSpriteTexture tex)
{
	std::transform(texname.begin(), texname.end(), texname.begin(), ::toupper);
	this->insert(std::pair<std::string, vbSpriteTexture>(texname, tex));
}

vbSpriteTexture* vbImageMap::getTexturePtr(std::string str, BOOL searchOnly)
{
	std::transform(str.begin(), str.end(), str.begin(), ::toupper);
	vbImageMap::iterator it = this->find(str);
	if (it != this->end())
		return &this->at(str);
	else
	{
		if (!searchOnly)
		{
			string msg = "TEXTURE '" + str + "' NOT FOUND";
			PANIC(msg.c_str());
		}
		return NULL;
	}
}

vbSpriteTexture* vbImageMap::operator [](std::string str)
{
	return getTexturePtr(str);
}
