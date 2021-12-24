#pragma once

class vbGame
{
public:
	Vector2 gameResolution = { 0, 0 };
	vbCanvas* GUI = NULL;

	vbGame(Vector2 _gameResolution, vbString title);
	~vbGame() noexcept;
	vbGame(const vbGame& other) = delete;
	vbGame& operator=(const vbGame& other) = delete;
	bool vbGameShouldClose() const;
	virtual void update() {};
	virtual void render() {};
};

extern vbGame* pGAME;