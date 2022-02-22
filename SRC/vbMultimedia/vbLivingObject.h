#ifndef VBLIVINGOBJECT_H
#define VBLIVINGOBJECT_H

#include "basetypes.h"
#include <functional>

class vbGameObject
{
private:
	BOOL initialized = FALSE;
public:
	//std::function<void()> lupdate = NULL; //Called every tick BEFORE "render" and before any other logic.
	//std::function<void()> lrender = NULL; //Called every tick AFTER "update" and after any logic (tweens sequence, etc..). Place here custom direct rendering draw functions

	virtual void setup() {};

	virtual void update() {};

	virtual void draw() {};

	BOOL isAlive = TRUE; //Enables the "Update" and "Render" functions
	BOOL enabled = TRUE; //Enables or disable the "Update" function 
	vbGameObject();
	~vbGameObject();
};

#endif // !VBLIVINGOBJECT_H