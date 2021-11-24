#pragma once
#include "basetypes.h"
#include <functional>
//
class vbGame;
class vbData;
extern vbData* pDATA;
extern vbGame* pGAME;

class vbLivingObject
{
private:
	BOOL initialized = FALSE;
protected:
	vbGame* GAME = NULL;
	vbData* DATA = NULL;
public:
	std::function<void()> lupdate = NULL; //Called every tick BEFORE "render" and before any other logic.
	std::function<void()> lrender = NULL; //Called every tick AFTER "update" and after any logic (tweens sequence, etc..). Place here custom direct rendering draw functions
	virtual void init() {}; //Called once
	virtual void update() {}; //Called once
	virtual void render() {}; //Called once

	BOOL isAlive = FALSE; //Enables the "Update" and "Render" functions
	BOOL enabled = TRUE; //Enables or disable the "Update" function 
	vbLivingObject(vbGame* game = pGAME, vbData* data = pDATA);
	~vbLivingObject();
};

