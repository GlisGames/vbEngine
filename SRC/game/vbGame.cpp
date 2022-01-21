#include <vbEngine.h>

vbGame::vbGame()
{
	this->mainScene = new vbCanvas({ 0, 0, 0, 0 });
}

vbGame::~vbGame() noexcept
{
	CloseWindow();
}

bool vbGame::GameShouldClose() const
{
	return WindowShouldClose();
}

void vbGame::setLanguage(vbString langCode)
{
	this->language = &this->languages.getLang(langCode);
}

void vbGame::setState(TYPE_GAME_STATE newState)
{
	for (WORD i = 0; i < this->stateList.size(); i++)
	{
		if (this->stateList[i]->stateID == newState)
		{
			this->currentState = this->stateList[i];
			return;
		}
	}
	PANIC(TextFormat("ERROR, GAME STATE %d NOT SUPPORTED", newState));
}


// SOUNDMAP*********************************//
Sound vbSoundMap::operator [](std::string str)
{
	Sound empty;
	std::transform(str.begin(), str.end(), str.begin(), ::toupper);
	vbSoundMap::iterator it = this->find(str);
	if (it != this->end())
		return this->at(str);
	else
	{
		string msg = "SOUND '" + str + "' NOT FOUND";
		PANIC(msg.c_str());
		return empty;
	}
}

void vbSoundMap::addSound(std::string texname, Sound tex)
{
	this->insert(std::pair<std::string, Sound>(texname, tex));
}

// STYLES ******************************************//
styleElement* vbGame::style(vbString element_name)
{
	if (this->currentStyle != NULL)
		return this->currentStyle->checkName(element_name);
	else
		return NULL;
}

void vbGame::setStyle(vbContainer* c, vbString stylename)
{
	vbStyle* newstyle = this->styles.checkName(stylename);
	if (newstyle != NULL)
		this->currentStyle = newstyle;

	gObjectList* objList = NULL;
	objList = &c->gObjects;

	for (auto it = objList->begin(); it != objList->end(); it++)
	{
		styleElement* prop = newstyle->checkName((*it)->name);
		if (prop != NULL)
		{
			(*it)->applyStyle(prop);
		}
		if ((*it)->type == TYPE_CONTAINER)
			this->setStyle((vbContainer*)(*it), stylename);
	}
}