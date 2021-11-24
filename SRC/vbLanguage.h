#ifndef VBLANGUAGE_H
#define VBLANGUAGE_H
#include "basetypes.h"
#include "json.h"
#include "vector"
#include "vbFont.h"
#include <hb.h>
#include "vbTextBox.h"
using namespace std;

#define ARABIC		"ar"
#define ENGLISH		"en"
#define SPANISH		"es"
#define FRENCH		"fr"
#define ITALIAN		"it"
#define CHINESE		"zh"
#define GERMAN		"de"
#define VIETNAMESE	"vn"
#define TURKISH		"tr"

class vbLanguage;

class vbLanguage
{
private:
	map<string, vbString> dictionary;
public:
	vbLanguage();
	int loadDictionary(void* gameptr, string jsonPath);
	Texture2D* flagTexture = NULL;
	vbString operator[] (string text);
	vbString get(string text);
	string language_code = "en";
	string languageName = "English";
	hb_direction_t direction;
	//vector<vbFont*> fonts;
	vector<std::pair<vbString, FontPtr>> fontList;

	void addFont(const char* fontName, FontPtr ptr)
	{
		std::pair<vbString, FontPtr>* check = findFont(fontName);
		if (check == NULL)
			fontList.push_back(std::make_pair(fontName, ptr));
		else
			*check = std::make_pair(fontName, ptr);
	}

	void addAliasFontName(const char* fontName, const char* alias)
	{
		std::pair<vbString, FontPtr>* f = this->findFont(fontName);
		if (f != NULL) //if the font exist
		{
			std::pair<vbString, FontPtr>* a = this->findFont(alias); //check if we already have an alias
			if (a == NULL) //if not
				fontList.push_back(std::make_pair(alias, f->second)); //insert the new alias
			else
				a->second = f->second; //otherwise replace the existing one
		}
		else
			PANIC(FormatText("ERROR: Font %s not found", fontName));
	}
	FontPtr getFont(const char* fontName)
	{
		std::pair<vbString, FontPtr>* ret = NULL;
		ret = findFont(fontName);
		if(ret == NULL)
			PANIC(FormatText("ERROR: Font %s not found", fontName)); //MAYBE remove
		return ret->second;
	}
	std::pair<vbString, FontPtr> *findFont(const char* fontName)
	{
		for (int i = 0; i < fontList.size(); i++)
		{
			if (TextIsEqual(fontList[i].first.c_str(), fontName))
				return &fontList[i];
		}
		return NULL;
	}
};

typedef struct t_language_prop
{
	hb_direction_t direction;
	hb_script_t script;
	hb_language_t language;
}LanguageProperties;

static std::map<string, LanguageProperties> lang_prop =
{
	{"en", {HB_DIRECTION_LTR, HB_SCRIPT_LATIN, hb_language_from_string("en", -1)}},
	{"fr", {HB_DIRECTION_LTR, HB_SCRIPT_LATIN, hb_language_from_string("fr", -1)}},
	{"it", {HB_DIRECTION_LTR, HB_SCRIPT_LATIN, hb_language_from_string("it", -1)}},
	{"es", {HB_DIRECTION_LTR, HB_SCRIPT_LATIN, hb_language_from_string("es", -1)}},
	{"de", {HB_DIRECTION_LTR, HB_SCRIPT_LATIN, hb_language_from_string("de", -1)}},
	{"tr", {HB_DIRECTION_LTR, HB_SCRIPT_LATIN, hb_language_from_string("tr", -1)}},
	{"zh", {HB_DIRECTION_LTR, HB_SCRIPT_HAN, hb_language_from_string("zh", -1)}},
	{"ar", {HB_DIRECTION_RTL, HB_SCRIPT_ARABIC, hb_language_from_string("ar", -1)}}
};

class LanguageList : public std::vector<vbLanguage>
{
public:
	vbLanguage& getLang(vbString langCode)
	{
		for (unsigned int i = 0; i < this->size(); i++)
		{
			if (this->at(i).language_code == langCode)
			{
				return this->at(i);
				break;
			}
		}
		for (unsigned int i = 0; i < this->size(); i++)
		{
			if (this->at(i).language_code == "en")
			{
				return this->at(i);
				break;
			}
		}
		return this->at(0);
	}

	void addCommonFont(const char* fontName, FontPtr ptr)
	{
		for (unsigned int i = 0; i < this->size(); i++)
		{
			this->at(i).addFont(fontName, ptr);
		}
	}
	void addCommonAliasFontName(const char* fontName, const char* alias)
	{
		for (unsigned int i = 0; i < this->size(); i++)
		{
			this->at(i).addAliasFontName(fontName, alias);
		}
	}
};
#endif
