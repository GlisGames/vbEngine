#pragma once
#include <basetypes.h>
#include <vbStyle.h>
#include <vbCanvas.h>
#include <vbImage.h>
#include <GUI.h>
#include <vbState.h>
#include <vbSequence.h>
#include <vbLanguage.h>
#include <vbTextEngine.h>


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
	//vbImage* background = NULL;
	//GUI* GUI;
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

	vbGame(Vector2 _gameResolution, vbString title);
	~vbGame() noexcept;
	vbGame(const vbGame& other) = delete;
	vbGame& operator=(const vbGame& other) = delete;
	bool vbGameShouldClose() const;
	virtual void update() {};
	virtual void render() {};
};

extern vbGame* pGAME;