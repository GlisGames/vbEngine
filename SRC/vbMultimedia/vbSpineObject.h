#ifndef VBSPINEOBJECT_H
#define VBSPINEOBJECT_H

#include "vbGraphicObject.h"
#include "spine-raylib.h"

class vbSpineObject : public vbGraphicObject
{
public:
	vbSpineObject(const char* atlas_path, const char* json_path, Vector2 _position = { 0,0 }, Vector2 scale = { 1,1 });

	spAtlas* atlas = NULL;
	spSkeletonJson* json;
	spSkeletonData* skeletonData;
	spSkeleton* skeleton;
	spAnimationStateData* animationStateData;
	spAnimationState* animationState;
	
	DWORD getAnimationDurationByName(const char* animation_name); // return time in millisecond
	void doAnimation(const char* animation_name, DWORD repeat, BOOL force = TRUE, FLOAT delayinSecond = 0.0f); // ONLY TRACK 0 IS USED
	void clearAnimation(DWORD track = 0); // using track indexed 0 for now 
	void update();
	void draw();

	~vbSpineObject();
};

#endif // !VBSPINEOBJECT_H
