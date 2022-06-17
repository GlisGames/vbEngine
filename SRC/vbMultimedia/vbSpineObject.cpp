#include "basetypes.h"
#include "vbSpineObject.h"

vbSpineObject::vbSpineObject(const char* atlas_path, const char* json_path, Vector2 _position)
{
    // Init spine
    position = { _position.x, _position.y, 0 };
    atlas = spAtlas_createFromFile(atlas_path, 0);
    json = spSkeletonJson_create(atlas);

    skeletonData = spSkeletonJson_readSkeletonDataFile(json, json_path);

    if (!skeletonData) {
        printf("%s\n", json->error);
        spSkeletonJson_dispose(json);
        printf("ERROR!\n");
    }

    spBone_setYDown(true);
    skeleton = spSkeleton_create(skeletonData);
    skeleton->scaleX = 0.5;
    skeleton->scaleY = 0.5;

    // Create the spAnimationStateData
    animationStateData = spAnimationStateData_create(skeletonData);
    animationState = spAnimationState_create(animationStateData);
    // Add the animation "walk" to track 0, without delay, and let it loop indefinitely
    int track = 0;
    int loop = 1;
    float delay = 0;
    spAnimationState_addAnimationByName(animationState, track, "flying", loop, delay);
    spAnimationState_addAnimationByName(animationState, 0, "flying", 1, 0);
    spAnimationState_update(animationState, .0f);
    spAnimationState_apply(animationState, skeleton);
    spSkeleton_updateWorldTransform(skeleton);
}

void vbSpineObject::update()
{
    spAnimationState_update(animationState, GetFrameTime());
    spAnimationState_apply(animationState, skeleton);
    spSkeleton_updateWorldTransform(skeleton);
}

void vbSpineObject::draw()
{
    drawSkeleton(skeleton, position, TRUE);
}

vbSpineObject::~vbSpineObject()
{
    spAtlas_dispose(atlas);
    spSkeleton_dispose(skeleton);
    texture_2d_destroy(); // Destroy textures loaded by spine
}