#ifndef VBGAME_H
#define VBGAME_H

#include "basetypes.h"
#include "vbStyle.h"
#include "vbCanvas.h"
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
	vbCanvas* mainScene = NULL;
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
	void setStyle(vbCanvas* c, vbString stylename);

	vbGame();
	~vbGame() noexcept;
	vbGame(const vbGame& other) {};
	vbGame& operator=(const vbGame& other) {};
	vbGame(const vbGame&& other) = delete;
	vbGame& operator=(const vbGame&& other) = delete;
	bool GameShouldClose() const;
	virtual void StateMachine() {};
	virtual void update() {};
	virtual void render() {};

	void setLanguage(vbString langCode);
	void setState(TYPE_GAME_STATE newState);
};

extern vbGame* pGAME;

#endif // !VBGAME_H