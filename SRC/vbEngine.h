#ifndef VBENGINE_H
#define VBENGINE_H
//BASE
#include "basetypes.h"
#include "vbErrors.h"
#include "vbGPIO.h"

#if defined(PLATFORM_WEB)
#include <emscripten/emscripten.h>
#include <emscripten/html5.h>
#endif

//GAME
#include "vbUtils.h"

//MULTIMEDIA
#include "raylib.h"
#include "utils.h" 
#include "json.h"
#include "vbGame.h"
#include "vbState.h"
#include "vbGUI.h"
#include "vbButton.h"
#include "vbTextBox.h"
#include "vbRenderer.h"
#include "vbImage.h"
#include "vbAtlas.h"
#include "vbContainer.h"
#include "vbTween.h"
#include "vbGraphicObject.h"
#include "vbProperty.h"
#include "vbImage.h"
#include "vbSequence.h"
#include "vbEasing.h"
#include "vbLivingObject.h"
#include "vbTextEngine.h"
#include "vbCanvas.h"
#include "vbLanguage.h"
#include "vbMessage.h"
#include "vbStyles.h"
#include "vbNumericBox.h"
#include "vbTimer.h"

using namespace std;

Image LoadImageRawFromBuffer(unsigned char* fileData, unsigned int dataSize, int width, int height, int format, int headerSize);

//class vbGame
//{
//private:
//	vbStyle *current_style;
//public:
//	vbGame() {};
//	vbContainer mainGame;
//	vbMessage* alertBox;
//	class vbGUI* GUI; //(forward declaration)
//	vbImage* mainBG;
//	vbState* currentState;
//	DWORD gameCredits = 0;
//	
//	std::vector<vbState*> stateList;
//	std::map<std::string, Image> imageMapLocal;
//	std::vector<Image> atlasList;
//
//	gObjectList clickList;
//	vbImageMap textureMap;
//	vbSequenceMap sequenceMap;
//	vbSoundMap sounds;
//	vbLanguage* language;
//	LanguageList languages;
//	vbStylesMap styles;
//	styleElement* style(vbString element_name);
//	void changeStyle(vbContainer* c, vbString stylename);
//	vbTextEngine textEngine;
//
//	Vector2 gameResolution;
//	Vector2 screenResolution;
//}/*vbGame*/;

/*
class vbState
{
private:
	WORD exitState = 0xFF;
protected:
	BOOL firstIn = TRUE;
	DWORD frame = 0;
	vbGame* GAME = NULL;
	vbData* DATA = NULL;

	virtual void init() {};
	virtual void exit() {};
	virtual void checkButton() {};
	virtual void update() {};

public:
	WORD stateID = 0xFF;
	vbState()
	{
		this->GAME = pGAME;
		this->DATA = pDATA;
		this->exitState = 0xFF;
		this->canvas = new vbCanvas({ 0,0, pGAME->gameResolution.x, pGAME->gameResolution.y });
		this->canvas->visible = FALSE;
		this->GAME->mainGame.addObject(this->canvas);
		this->GAME->alertBox = new vbMessage(NULL, {0, 0}, TRUE);
		this->GAME->alertBox->visible = FALSE;
		this->GAME->mainGame.addObject(this->GAME->alertBox, "alertBox");
		this->GAME->stateList.push_back(this);
	}
	void stateExit(WORD s)
	{
		this->exitState = s;
	};
	vbTweenMap tweens;
	vbContainer *canvas;
	BOOL afterAndEvery(DWORD after, DWORD every)
	{
		return (this->frame > after && !((this->frame + after) % every));
	}

	BOOL afterAndUntil(DWORD after, DWORD until)
	{
		return (this->frame > after && (this->frame < until));
	}

	BOOL afterAndEveryUntil(DWORD after, DWORD until, DWORD every)
	{
		return (this->frame > after && !((this->frame + after) % every) && (this->frame < until));
	}

	WORD run()
	{
		if (this->firstIn == TRUE)
		{
			this->exitState = 0xFF;
			this->frame = 0;
			this->init();
			this->firstIn = FALSE;
		}
		this->tweens.stepAll();
		this->checkButton();
		this->update();
		if (this->exitState != 0xFF)
		{
			this->exit();
			this->firstIn = TRUE;
			return this->exitState;
		}
		this->frame++;
		return 0xFF;
	};
};
*/


//extern vbGame* pGAME;

#endif