#include "basetypes.h"
#include "vbSpineObject.h"

vbSpineObject::vbSpineObject(const char* atlas_path, const char* json_path, Vector2 _position, Vector2 scale) : vbGraphicObject() // position center
{
    // Init spine
    position = { _position.x, _position.y};
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
    skeleton->scaleX = scale.x;
    skeleton->scaleY = scale.y;

    // Create the spAnimationStateData
    animationStateData = spAnimationStateData_create(skeletonData);
    animationState = spAnimationState_create(animationStateData);
}

DWORD vbSpineObject::getAnimationDurationByName(const char* animation_name)
{
    return spSkeletonData_findAnimation(skeletonData, animation_name)->duration * 1000;
}

void vbSpineObject::doAnimation(const char* animation_name, DWORD repeat, BOOL force, FLOAT delayinSecond)  // repeat = -1 : loop indefinitely
{
    if (force)    spAnimationState_clearTrack(animationState, 0);
    if (spSkeletonData_findAnimation(skeletonData, animation_name) == 0)
    {
        printf("animation doesn't exist.\n");
        return;
    }
    
    if (repeat == -1)
    {
        spAnimationState_addAnimationByName(animationState, 0, animation_name, 1, delayinSecond); // ONLY USE TRACK 0
    }
    else
    {
        for (int i = 0; i < repeat; i++)
        {
            spAnimationState_addAnimationByName(animationState, 0, animation_name, 0, delayinSecond); // ONLY USE TRACK 0
        }
    }
}

void vbSpineObject::clearAnimation(DWORD track)
{
    spAnimationState_clearTrack(animationState, 0);
}

void vbSpineObject::update()
{
    vbGraphicObject::update();

    spAnimationState_update(animationState, GetFrameTime());
    spAnimationState_apply(animationState, skeleton);
    if (!spAnimationState_getCurrent(animationState, 0))    return;
    spSkeleton_updateWorldTransform(skeleton);
}

void vbSpineObject::draw()
{
    vbGraphicObject::draw();

    drawSkeleton(skeleton, { position.x, position.y, 0 }, TRUE);
}

vbSpineObject::~vbSpineObject()
{
    spAtlas_dispose(atlas);
    spSkeleton_dispose(skeleton);
    texture_2d_destroy(); // Destroy textures loaded by spine
}