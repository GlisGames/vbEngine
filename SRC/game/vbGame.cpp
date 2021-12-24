#include "vbEngine.h"

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
