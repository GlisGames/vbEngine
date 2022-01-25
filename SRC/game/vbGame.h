#ifndef VBGAME_H
#define VBGAME_H

#include "basetypes.h"
#include "vbStyle.h"
#include "vbContainer.h"
#include "vbImage.h"
#include "vbState.h"
#include "vbSequence.h"
#include "vbLanguage.h"
#include "vbTextEngine.h"

class vbSoundMap : private std::map<std::string, Sound>
{
public:
	void addSound(std::string texname, Sound tex);
	Sound operator [](std::string str);
};

class vbGame
{
private:
	vbStyle* currentStyle;
public:
	Vector2 gameResolution = { 0, 0 };
	vbContainer* mainScene = NULL;
	vbState* currentState;
	std::vector<vbState*> stateList;
	std::map<std::string, Image> imageMapLocal;
	std::vector<Image> atlasList;

	vbImageMap textureMap;
	vbSequenceMap sequenceMap;
	vbSoundMap soundMap;
	vbStyleMap styles;

	vbLanguage* language;
	LanguageList languages;
	vbTextEngine textEngine;
	styleElement* style(vbString element_name);
	void setStyle(vbContainer* c, vbString stylename);

	virtual void init() = 0;
	vbGame();
	~vbGame() noexcept;
	bool GameShouldClose() const;
	virtual void StateMachine() {};
	virtual void update() {};
	virtual void render() {};

	void setLanguage(vbString langCode);
	void setState(TYPE_GAME_STATE newState);
};

extern vbGame* pGAME;

#endif // !VBGAME_H