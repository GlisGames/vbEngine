#include <vbEngine.h>

vbGame::vbGame(Vector2 _gameResolution, vbString _title)
{
	this->gameResolution = _gameResolution;
	InitWindow(this->gameResolution.x, this->gameResolution.y, _title.c_str());
}

vbGame::~vbGame() noexcept
{
	CloseWindow();
}

bool vbGame::vbGameShouldClose() const
{
	return WindowShouldClose();
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

void vbGame::setStyle(vbCanvas* c, vbString stylename)
{
	vbStyle* newstyle = this->styles.checkName(stylename);
	if (newstyle != NULL)
		pGAME->currentStyle = newstyle;

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
			this->setStyle((vbCanvas*)(*it), stylename);
	}
}