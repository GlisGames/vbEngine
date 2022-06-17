#ifndef VBSPINEOBJECT_H
#define VBSPINEOBJECT_H

#include "spine-raylib.h"

class vbSpineObject
{
public:
	vbSpineObject(const char* atlas_path, const char* json_path, Vector2 _position);

	spAtlas* atlas = NULL;
	spSkeletonJson* json;
	spSkeletonData* skeletonData;
	spSkeleton* skeleton;
	spAnimationStateData* animationStateData;
	spAnimationState* animationState;
	Vector3 position;

	void update();
	void draw();

	~vbSpineObject();
};

#endif // !VBSPINEOBJECT_H
