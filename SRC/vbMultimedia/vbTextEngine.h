#ifndef VBTEXTENGINE_H
#define VBTEXTENGINE_H
#include "basetypes.h"
#include <hb.h>
#include "text_run.h"
//#include "scope_guard.h"
#include "text_render.h"
#include "vbLanguage.h"

class vbTextEngine
{
private:
	FT_Library ft;
public:
	vbTextEngine() {};
	int init()
	{
		//FT_Library ft;
		if (FT_Init_FreeType(&ft))
		{
			fprintf(stderr, "FT_Init_FreeType failed\n");
			//TODO handle freetype init error
			return 1;
		}
		if (!this->render.Init(4)) //FIXME text render only 4 atlas..
			return 1;

		return 0;
	};
	FT_Library* getFTreference(){return &this->ft;}
	//std::vector<vbLanguage> languages;
	LanguageList languages;
	TextRender render;
};

#endif
