#ifndef VBSTYLES_H
#define VBSTYLES_H
#include "basetypes.h"
#include "vbErrors.h"
#include "vbContainer.h"
#include "json.h"
#include "vector"
#include <string>

class vbGame;

typedef struct styleElement
{
	Vector2* position;
	Vector2* size;
	Texture2D* texture;
};

class vbStyle : public map <vbString, styleElement>
{
public:
	styleElement vbStyle::operator [](vbString str)
	{
		styleElement *ret = checkName(str);
		if (ret == NULL)
		{	string msg = "STYLE name '" + str + "' NOT FOUND";
			PANIC(msg.c_str());
		}
		else
			return *ret;
	}

	styleElement* checkName(vbString str)
	{
		std::transform(str.begin(), str.end(), str.begin(), ::toupper);
		vbStyle::iterator it = this->find(str);
		if (it != this->end())
			return &this->at(str);
		else
			return NULL;
	}
};

class vbStylesMap : public map <vbString, vbStyle>
{
public:
	vbStyle vbStylesMap::operator [](vbString str)
	{
		vbStyle* ret = checkName(str);
		if (ret == NULL)
		{
			string msg = "STYLE name '" + str + "' NOT FOUND";
			PANIC(msg.c_str());
		}
		return *ret;
	}

	vbStyle* checkName(vbString str)
	{
		std::transform(str.begin(), str.end(), str.begin(), ::toupper);
		vbStylesMap::iterator it = this->find(str);
		if (it != this->end())
			return &this->at(str);
		else
			return NULL;
	}

	BYTE loadStyle(vbString stylename, vbString filename);
	void changeStyle(vbContainer* c, vbString stylename);
};

#endif